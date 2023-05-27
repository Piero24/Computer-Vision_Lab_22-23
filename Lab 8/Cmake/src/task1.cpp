// task1.cpp
// g++ -std=c++11 -o task1 task1.cpp -I/usr/local/include/opencv4/ -lopencv_core -lopencv_highgui -lopencv_imgcodecs -lopencv_imgproc -lopencv_features2d -lopencv_calib3d
// ./task1 ./data/checkerboard_images/

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

#include <opencv2/core/mat.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/xfeatures2d/nonfree.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/calib3d.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

void task1(int argc, char** argv) {

	std::vector<cv::String> folderFilePaths;
	std::vector<cv::Mat> imagesVec;

    cv::glob(argv[1], folderFilePaths, false);

    size_t numFiles = folderFilePaths.size();
    for (size_t i = 0; i < numFiles; i++) {
        if (folderFilePaths[i].substr(folderFilePaths[i].size() - 4) == ".jpg" ||
            folderFilePaths[i].substr(folderFilePaths[i].size() - 4) == ".png" ||
            folderFilePaths[i].substr(folderFilePaths[i].size() - 4) == ".bmp") {

            cv::Mat img = cv::imread(folderFilePaths[i]);
            imagesVec.push_back(img);
        }
    }

    // Chessboard constants
	static const int CHESSBOARD_WIDTH = 6;
	static const int CHESSBOARD_HEIGHT = 5;
    cv::Size chessboardSize(CHESSBOARD_HEIGHT, CHESSBOARD_WIDTH);

    // Data after finding patterns
	std::vector<std::vector<cv::Point2f>> imagePoints;
	std::vector<std::vector<cv::Point3f>> objectPoints;

    std::vector<cv::Point3f> points;
	for (int i = 0; i < CHESSBOARD_WIDTH; i++) {
		for (int j = 0; j < CHESSBOARD_HEIGHT; j++) {
			points.push_back(cv::Point3f(j, i, 0));
		}
	}

    size_t totalImages = imagesVec.size();
    for (size_t i = 0; i < totalImages; i++) {
        std::vector<cv::Point2f> corners;
        cv::Mat grayImage;

		cv::cvtColor(imagesVec.at(i), grayImage, cv::COLOR_BGR2GRAY);

        bool success = findChessboardCorners(grayImage, chessboardSize, corners);

        if (success) {
			objectPoints.push_back(points);
			imagePoints.push_back(corners);
		}
    }

    cv::Mat cameraMatrix, distCoeff;
	std::vector<cv::Mat> rvecs, tvecs;	

	cv::calibrateCamera(objectPoints, imagePoints,
		cv::Size(CHESSBOARD_HEIGHT, CHESSBOARD_WIDTH), cameraMatrix, distCoeff, rvecs, tvecs);
    
    float meanError = 0;
	for (int i = 0; i < objectPoints.size(); i++) {
		std::vector<cv::Point2f> projectedPoints;
		cv::projectPoints(objectPoints.at(i), rvecs.at(i), tvecs.at(i), cameraMatrix, distCoeff, projectedPoints);
		meanError += cv::norm(imagePoints.at(i), projectedPoints, cv::NORM_L2) / projectedPoints.size();
	}
	meanError = meanError / objectPoints.size();

    //std::cout << "MEAN REPROJECTION ERROR: " << meanError << std::endl;

    std::vector<cv::Mat> outputImages;
    int imageIndex = 9;

	cv::Mat image;
	cv::cvtColor(imagesVec.at(imageIndex), image, cv::COLOR_BGR2GRAY);

	cv::Rect roi;
	cv::Mat newCameraMatrix = cv::getOptimalNewCameraMatrix(cameraMatrix, distCoeff,
		cv::Size(image.cols, image.rows), 1, cv::Size(image.cols, image.rows), &roi);

	cv::Mat map1, map2;
	cv::initUndistortRectifyMap(cameraMatrix, distCoeff, cv::Mat(),
		newCameraMatrix, cv::Size(image.cols, image.rows), 5, map1, map2);

	cv::Mat distortedImage;
	cv::remap(image, distortedImage, map1, map2, cv::INTER_LINEAR);

	cv::Mat resizedImage(roi.height, roi.width, CV_8UC1);
	for (int i = roi.y; i < roi.y + roi.height; i++) {
		for (int j = roi.x; j < roi.x + roi.width; j++) {
			resizedImage.at<unsigned char>(i - roi.y, j - roi.x) = distortedImage.at<unsigned char>(i, j);
		}
	}

	outputImages.push_back(image);
	outputImages.push_back(resizedImage);	

	int rows = std::max(outputImages.at(0).rows, outputImages.at(1).rows);
	cv::Mat finalImage(rows, outputImages.at(0).cols + outputImages.at(1).cols, CV_8UC1);


	rows = std::min(std::max(outputImages.at(0).rows, outputImages.at(1).rows), outputImages.at(0).rows);
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < outputImages.at(0).cols; j++) {
			finalImage.at<unsigned char>(i, j) = outputImages.at(0).at<unsigned char>(i, j);
		}
	}


	rows = std::min(std::max(outputImages.at(0).rows, outputImages.at(1).rows), outputImages.at(1).rows);
	for (int i = 0; i < rows; i++) {
		for (int j = outputImages.at(0).cols; j < outputImages.at(0).cols + outputImages.at(1).cols; j++) {
			finalImage.at<unsigned char>(i, j) = outputImages.at(1).at<unsigned char>(i, j - (outputImages.at(0).cols));
		}
	}

	cv::imwrite("output.png", finalImage);
	cv::imshow("OUTPUT", finalImage);
	cv::waitKey(0);
}
