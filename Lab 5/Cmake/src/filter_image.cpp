#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "../include/funcTask1.h"


cv::Mat filter_image(cv::Mat image, cv::Mat mask) {

    cv::Mat inverted_mask;
    cv::bitwise_not(mask, inverted_mask);

    cv::Mat result;
    image.copyTo(result, inverted_mask);

    cv::Mat background = cv::Mat::zeros(image.size(), image.type());
    background.setTo(cv::Scalar(255, 255, 255));
    background.copyTo(result, mask);

    return result;
}

