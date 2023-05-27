#ifndef FUNCTASK1_H
#define FUNCTASK1_H

#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/core/types.hpp>

cv::Mat thresholdOtsu(cv::Mat img);
cv::Mat filter_image(cv::Mat image, cv::Mat mask);


#endif //FUNCTASK1_H