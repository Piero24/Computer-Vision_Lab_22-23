// task1.cpp
// g++ -std=c++11 -o task1 task1.cpp -I/usr/local/include/opencv4/ -lopencv_core -lopencv_highgui -lopencv_imgcodecs -lopencv_imgproc -lopencv_features2d
// ./task1 Images/img1.png Images/img2.png
// ./task1 Images/all_souls_000006.jpg Images/all_souls_000002.jpg
// ./task1 Images/bodleian_000192.jpg Images/bodleian_000167.jpg


#include <iostream>
// /usr/local/Cellar/opencv/4.7.0_1/include/opencv4
#include <vector>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/features2d.hpp>
#include <algorithm>
#include "../include/funcTask1.h"


void task1(int argc, char** argv) {

    std::string strImg = argv[1];
    std::string strImg2 = argv[2];

    if (strImg.substr(strImg.size() - 4) == ".jpg" || strImg.substr(strImg.size() - 4) == ".png") {

        strImg.erase(strImg.size() - 4);
    }
    if (strImg2.substr(strImg2.size() - 4) == ".jpg" || strImg2.substr(strImg2.size() - 4) == ".png") {

        strImg2.erase(strImg2.size() - 4);
    }

    cv::Mat img = cv::imread(argv[1]);
    cv::Mat img2 = cv::imread(argv[2]);

    cv::Mat grayImg;
    cv::Mat grayImg2;

    cv::cvtColor(img, grayImg, cv::COLOR_BGR2GRAY);
    cv::cvtColor(img2, grayImg2, cv::COLOR_BGR2GRAY);

    // Initiate ORB Detector Class within pointer.
	cv::Ptr <cv::FeatureDetector> detector = cv::ORB::create();

    // Finding key points.
	std::vector <cv::KeyPoint> keypoints_base_image;
	std::vector <cv::KeyPoint> keypoints_locate_image;

	// Find keypoints.
	detector -> detect(img, keypoints_base_image);
	detector -> detect(img2, keypoints_locate_image);

    detector.release();

	// Find descriptors.
	cv::Mat descriptors_base_image;
	cv::Mat descriptors_locate_image;

    cv::Ptr <cv::DescriptorExtractor> extractor = cv::ORB::create();

    extractor -> compute(img, keypoints_base_image, descriptors_base_image);
	extractor -> compute(img2, keypoints_locate_image, descriptors_locate_image);

	extractor.release();

	// Create Brute-Force Matcher. Other Algorithms are 'non-free'.
	cv::BFMatcher brue_force_matcher = cv::BFMatcher(cv::NORM_HAMMING, true);

    // Vector where matches will be stored.
	std::vector <cv::DMatch> matches;
    int match_treshold = 41;
    int match_treshold_count = 0;

	// Find matches and store in matches vector.
	brue_force_matcher.match(descriptors_base_image, descriptors_locate_image,  matches);

    // Ordina il vettore delle corrispondenze in base alla distanza minore
    std::sort(matches.begin(), matches.end(), compareMatches);

    if (matches.size() > 10) {
		matches.resize(10);
	}

	// Draw the first 10 matches
	cv::Mat output_image;

	std::cout << "Keypoints Base Size:" << keypoints_base_image.size() << std::endl
			  << "Keypoints Locate Size:" << keypoints_locate_image.size() << std::endl
			  << "Matches Size:" << matches.size() << std::endl;

    std::cout << "First "<< matches.size() <<" Match Distance's:" << std::endl;

    for (int i = 0; i < matches.size(); i++)
    {
        std::cout << matches[i].distance << ", ";
    }

    std::cout << std::endl;

    for (int i = 0; i < matches.size(); i++) {
        if (matches[i].distance <= match_treshold) {
            match_treshold_count++;
        }
	}

    if (match_treshold_count >= 7) {

        cv::drawMatches(
                        img, keypoints_base_image,
                        img2, keypoints_locate_image,
                        matches,
                        output_image);

        //cv::namedWindow(strImg);
        //cv::namedWindow(strImg2);
        //cv::imshow(strImg, img);
        //cv::imshow(strImg2, img2);

        cv::imwrite("outputImg.png", output_image);

        cv::namedWindow("Matches");
        cv::imshow("Matches", output_image);
        cv::waitKey(0);
        cv::destroyAllWindows();

    } else {
        std::cout << "Match probability is below 70%.\nNot sufficient match found."<< std::endl;
        std::cout << match_treshold_count << std::endl;
    }

}
