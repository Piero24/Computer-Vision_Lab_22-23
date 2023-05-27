#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "../include/funcTask1.h"


cv::Mat thresholdOtsu(cv::Mat img) {

    cv::Mat imgGray;
    cv::cvtColor(img, imgGray, cv::COLOR_RGB2GRAY);

    // Pre treshold otsu erode
    cv::Mat kernel1 = cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(1, 1));
    cv::erode(imgGray, imgGray, kernel1);

    double alpha = 0.36;
	int beta = 239;

    // Increase the brightness
    cv::Mat plusBright;
    imgGray.convertTo(plusBright, -1, alpha, beta);

    // Pre treshold otsu Gaussian Blur
    cv::Mat blurredImg;
    cv::GaussianBlur(plusBright, blurredImg, cv::Size(11, 11), 0);

    // Apply treshold otsu
    cv::Mat clonedImage = cv::Mat::zeros(img.size(), img.type());
    cv::threshold(blurredImg, clonedImage, 0, 255, cv::THRESH_OTSU);

    // Post treshold otsu erode
    cv::Mat kernel2 = cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(7, 7));
    cv::erode(clonedImage, clonedImage, kernel2);
    
    // Post treshold otsu dilate
    cv::Mat kernel3 = cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(7, 7));
    cv::dilate(clonedImage, clonedImage, kernel3);

    return clonedImage;
}
