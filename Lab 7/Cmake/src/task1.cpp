// task1.cpp
// g++ -std=c++11 -o task1 task1.cpp -I/usr/local/include/opencv4/ -lopencv_core -lopencv_highgui -lopencv_imgcodecs -lopencv_imgproc -lopencv_features2d -lopencv_calib3d Image/PanoramicUtils/panoramic_utils.cpp
// ./task1 Image/Images/data/
// ./task1 Image/Images/dolomites/
// ./task1 Image/Images/kitchen/
// ./task1 Image/Images/dataset_lab_19_automatic/
// ./task1 Image/Images/dataset_lab_19_manual/

#include <string>
#include <vector>
#include <iostream>

#include <opencv2/core/mat.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/xfeatures2d/nonfree.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/calib3d.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "../include/panoramic_utils.h"


void task1(int argc, char** argv) {

	std::vector<cv::Mat> imagesProjected;
	std::vector<cv::Mat> descriptors;
	std::vector<std::vector<cv::KeyPoint>> keypoints;

	std::vector<cv::String> fileInFolderVec;

    int ratio = 10;
	int FoV;

	std::string input;
    std::cout << "Inserisci il valore di FoV (es: 66° or 54°): ";
    std::cin >> input;

    try {

        FoV = std::stoi(input);
        FoV /= 2;

    } catch (const std::invalid_argument& e) {
        std::cerr << "Error: The value entered for FoV is not an integer." << std::endl;
        std::cerr << "Please try again by entering a valid integer.\n" << std::endl;
        return;
    }

    cv::glob(argv[1], fileInFolderVec, false);

    size_t count = fileInFolderVec.size();
    for (size_t i = 0; i < count; i++) {
        if (fileInFolderVec[i].substr(fileInFolderVec[i].size() - 4) == ".jpg" ||
            fileInFolderVec[i].substr(fileInFolderVec[i].size() - 4) == ".png" ||
            fileInFolderVec[i].substr(fileInFolderVec[i].size() - 4) == ".bmp") {

            cv::Mat img = cv::imread(fileInFolderVec[i]);
            cv::Mat tmpImg = cylindricalProj(img, FoV);
            imagesProjected.push_back(tmpImg);
        }
    }

	//Extract and save keypoints and descriptos
	cv::Ptr<cv::FeatureDetector> detector = cv::ORB::create();

	for (cv::Mat img : imagesProjected) {

		cv::Mat des;
		std::vector<cv::KeyPoint> keyp;

		detector -> detectAndCompute(img, cv::noArray(), keyp, des);
		descriptors.push_back(des);
		keypoints.push_back(keyp);
	}

	//Match features
	std::vector< std::vector<cv::DMatch>> matches;

	cv::BFMatcher matcher(cv::NORM_L2);

	for (int i = 0; i < imagesProjected.size() - 1; i++) {

		cv::Mat descriptors1 = descriptors.at(i);
		cv::Mat descriptors2 = descriptors.at(i + 1);

		std::vector<cv::KeyPoint> keypoints1 = keypoints.at(i);
		std::vector<cv::KeyPoint> keypoints2 = keypoints.at(i + 1);

		std::vector<cv::DMatch> tempMatches;
		matcher.match(descriptors1, descriptors2, tempMatches);

		matches.push_back(tempMatches);
	}

	//Refine descriptors
	std::vector< std::vector<cv::DMatch>> refinedFeatures;
	
	for (std::vector<cv::DMatch> featuresI : matches) {

		sort(featuresI.begin(), featuresI.end());
		float threshold = featuresI.at(0).distance * ratio;
		
		std::vector<cv::DMatch> matchesRefined;
		
		for (int i = 0; i < featuresI.size(); i++) {

			if (featuresI.at(i).distance < threshold) {
				matchesRefined.push_back(featuresI.at(i));
			}
		}
		refinedFeatures.push_back(matchesRefined);
	}

	//std::cout << refinedFeatures.size();


	//Compute matrixTranslations
	std::vector<int> indices;
	std::vector<cv::Mat> matrices;

	for (int i = 0; i < refinedFeatures.size() - 1; i++) {

		//can only do operations for size > 4
		if (refinedFeatures.at(i).size() > 4) {

			std::vector<cv::DMatch> featuresI = refinedFeatures.at(i);

			std::vector<cv::Point2f> srcPoints;
			std::vector<cv::Point2f> dstPoints;
			
			for (int j = 0; j < featuresI.size(); j++) {
				srcPoints.push_back(keypoints.at(i).at(featuresI.at(j).queryIdx).pt);
				dstPoints.push_back(keypoints.at(i + 1).at(featuresI.at(j).trainIdx).pt);
			}
			
			matrices.push_back(cv::findHomography(srcPoints, dstPoints, cv::RANSAC));
			indices.push_back(i);
		}
	}

	//Combine Images
	cv::Mat img = imagesProjected.at(indices.at(0));
	int threshold = img.cols;
	cv::Mat finalImage;
	
	cv::warpPerspective(img, finalImage, matrices.at(0),
		cv::Size(img.cols * indices.size(), img.rows));

	int col = finalImage.cols-1;
	cv::Mat thrs1 = 255 - finalImage;
	for (int x = col; x >= 0; x--) {
		if (thrs1.at<unsigned char>(finalImage.rows/2, x) != 255) {
			if (x < threshold) {
				col = x;				
				break;				
			}
		}
	}		

	int offset = 0;

	for (int r = 0; r < imagesProjected.at(indices.at(0) + 1).rows; r++) {
		for (int c = 0; c < imagesProjected.at(indices.at(0) + 1).cols; c++) {
			finalImage.at<unsigned char>(r, c + offset) = imagesProjected.at(indices.at(0) + 1).at<unsigned char>(r, c);
		}
	}

	int totalSize = col + (imagesProjected.at(indices.at(0) + 1).cols - col);

	for (int i = 1; i < indices.size(); i++) {

		//take next image
		img = imagesProjected.at(indices.at(i));

		//apply warpPerspective
		cv::Mat warp;
		cv::warpPerspective(img, warp, matrices.at(i),
			cv::Size(img.cols + imagesProjected.at(indices.at(i) + 1).cols, img.rows));

		//compute warp col
		int colWarp = warp.cols-1;
		cv::Mat thrs2 = 255 - warp;
		for (int x = colWarp; x >= 0; x--) {
			if (thrs2.at<unsigned char>(warp.rows/2, x) != 255) {
				if (x < threshold) {				
					colWarp = x;
					break;			
				}
			}
		}				

		offset += (imagesProjected.at(indices.at(i) + 1).cols - col);	

		for (int r = 0; r < imagesProjected.at(indices.at(i) + 1).rows; r++) {
			for (int c = 0; c < imagesProjected.at(indices.at(i) + 1).cols; c++) {
				finalImage.at<unsigned char>(r, c + offset) = imagesProjected.at(indices.at(i) + 1).at<unsigned char>(r, c);
			}
		}

		totalSize += ((colWarp + (imagesProjected.at(indices.at(i) + 1).cols - colWarp)) - offset);
		
		col = colWarp;
	}

	int colFinal = offset + imagesProjected.at(indices.size() - 1).cols;
	cv::Mat actualFinal(finalImage.rows, colFinal, finalImage.type());

	for (int r = 0; r < finalImage.rows; r++) {
		for (int c = 0; c < colFinal; c++) {
			actualFinal.at<unsigned char>(r, c) = finalImage.at<unsigned char>(r, c);
		}
	}
	
	cv::namedWindow("PANORAMA");
	cv::imshow("PANORAMA",actualFinal);
	cv::waitKey(0);

}
