// task1.cpp
// g++ -std=c++11 -o task1 task1.cpp -I/usr/local/include/opencv4/ -lopencv_core -lopencv_highgui -lopencv_imgcodecs -lopencv_imgproc
// ./task1 street_scene.png

#include <iostream>
// /usr/local/Cellar/opencv/4.7.0_1/include/opencv4
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "opencv2/imgcodecs.hpp"

const int alpha_slider_max = 1000;
const int alpha_slider_max_2 = 1000;
int alpha_slider;
int alpha_slider_2;

cv::Mat img;
cv::Mat cannyImg;

static void on_trackbar(int, void*);

void task1(int argc, char** argv) {

    std::string str = argv[1];
    alpha_slider = 0;
    alpha_slider_2 = 0;

    img = cv::imread(argv[1]);
    cv::namedWindow("Slider");

    cv::createTrackbar("First ", "Slider", &alpha_slider, alpha_slider_max, on_trackbar);
    cv::createTrackbar("Second ", "Slider", &alpha_slider_2, alpha_slider_max_2, on_trackbar);
    on_trackbar(0, 0);

    cv::waitKey(0);
    cv::destroyAllWindows();
}


static void on_trackbar(int, void*) {
    cv::Canny(img, cannyImg, alpha_slider, alpha_slider_2);
    imshow("Slider", cannyImg);
}