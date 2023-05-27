
#include <iostream>
// /usr/local/Cellar/opencv/4.7.0_1/include/opencv4
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include "maxFilter.h"

// Max Filter
cv::Mat maxFilter(cv::Mat img, int kernelSize) {

    cv::Mat maxImage = img.clone();
    int halfSize = kernelSize / 2;

    if (kernelSize % 2 == 0) {
        std::cerr << "Error: Kernel size must be odd." << std::endl;
        return maxImage;
    }

    for (int row = 0; row < maxImage.rows - kernelSize; row++) {
            for (int col = 0; col < maxImage.cols - kernelSize; col++) {

                cv::Vec3b maxVal(0, 0, 0);

                for (int kernelRow = 0; kernelRow < kernelSize; kernelRow++) {
                    for (int kernelCol = 0; kernelCol < kernelSize; kernelCol++) {

                        cv::Vec3b val = img.at<cv::Vec3b>(row + kernelRow, col + kernelCol);
                        if (val[0] > maxVal[0]) {
                            maxVal[0] = val[0];
                        }
                        if (val[1] > maxVal[1]) {
                            maxVal[1] = val[1];
                        }
                        if (val[2] > maxVal[2]) {
                            maxVal[2] = val[2];
                        }
                    }
                }
                maxImage.at<cv::Vec3b>(row + halfSize, col + halfSize)= maxVal;

            }
        }

    return maxImage;
}