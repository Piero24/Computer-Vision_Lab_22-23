// task2.cpp
// g++ -std=c++11 -o task2 task2.cpp -I/usr/local/include/opencv4/ -lopencv_core -lopencv_highgui -lopencv_imgcodecs -lopencv_imgproc
// ./task2 street_scene.png

#include <iostream>
// /usr/local/Cellar/opencv/4.7.0_1/include/opencv4
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "opencv2/imgcodecs.hpp"


void task2(int argc, char** argv) {

    std::string str = argv[1];
    cv::Mat img = cv::imread(argv[1]);
    cv::Mat cannyImg;
    cv::Canny(img, cannyImg, 845, 435);
    cv::Mat maskImage = cv::Mat::zeros(cannyImg.size(), cannyImg.type());

    cv::Vec3b bianco(255, 255, 255);
    int threshold = 20;

    for (int row = 1; row < img.rows; row++) {
        for (int col = 1; col < img.cols; col++) {

            if (cannyImg.at<uchar>(row, col) > 0) {

                for (int i = row - 1; i < row + 2; i++) {
                    for (int j = col - 1; j < col + 2; j++) {

                        cv::Vec3b valToCheck = img.at<cv::Vec3b>(i, j);

                        if (((valToCheck[0] <= bianco[0]) && (valToCheck[0] >= (bianco[0] - threshold))) && 
                            ((valToCheck[1] <= bianco[1]) && (valToCheck[1] >= (bianco[1] - threshold))) && 
                            ((valToCheck[2] <= bianco[2]) && (valToCheck[2] >= (bianco[2] - threshold)))) {

                            maskImage.at<uchar>(i, j) = 255;
                            
                        }
                    }
                }
            }
        }
    }

    for (int row = 5; row < maskImage.rows - 7; row++) {
        for (int col = 5; col < maskImage.cols - 7; col++) {

            if (maskImage.at<uchar>(row, col) > 0) {

                int PxCount = 0;

                for (int i = row - 5; i < row + 7; i++) {
                    for (int j = col - 5; j < col + 7; j++) {

                        if (maskImage.at<uchar>(i, j) == 255) {
                            PxCount++;
                        }
                    }
                }

                if (PxCount < 13) {
                    maskImage.at<uchar>(row, col) = 0;
                }
            }  

            if (maskImage.at<uchar>(row, col) > 0) {

                for (int i = row - 5; i < row + 7; i++) {
                    for (int j = col - 5; j < col + 7; j++) {

                        if (img.at<cv::Vec3b>(i, j) == bianco) {
                            maskImage.at<uchar>(i, j) = 255;
                        }
                    }
                }
            }
        }
    }



    cv::namedWindow("Canny");
    cv::imshow("Canny", maskImage);
    cv::waitKey(0);
    cv::destroyAllWindows();
}