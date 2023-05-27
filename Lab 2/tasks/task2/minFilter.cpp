#include <iostream>
// /usr/local/Cellar/opencv/4.7.0_1/include/opencv4
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include "minFilter.h"

//Min Filter
cv::Mat minFilter(cv::Mat img, int kernelSize) {

    cv::Mat minImage = img.clone();
    int halfSize = kernelSize / 2;

    if (kernelSize % 2 == 0) {
        std::cerr << "Errore: la dimensione del kernel deve essere dispari." << std::endl;
        return minImage;
    }

    for (int row = 0; row < minImage.rows - kernelSize; row++) {
            for (int col = 0; col < minImage.cols - kernelSize; col++) {

                cv::Vec3b minVal(0, 0, 0);

                for (int kernelRow = 0; kernelRow < kernelSize; kernelRow++) {
                    for (int kernelCol = 0; kernelCol < kernelSize; kernelCol++) {

                        cv::Vec3b val = img.at<cv::Vec3b>(row + kernelRow, col + kernelCol);
                        if (val[0] < minVal[0]) {
                            minVal[0] = val[0];
                        }
                        if (val[1] < minVal[1]) {
                            minVal[1] = val[1];
                        }
                        if (val[2] < minVal[2]) {
                            minVal[2] = val[2];
                        }
                    }
                }
                minImage.at<cv::Vec3b>(row + halfSize, col + halfSize)= minVal;

            }
        }

    return minImage;
}