// task4.cpp
// g++ -std=c++11 -o task4 task4.cpp -I/usr/local/include/opencv4/ -lopencv_core -lopencv_highgui -lopencv_imgcodecs -lopencv_imgproc
// ./task4 street_scene.png

#include <iostream>
// /usr/local/Cellar/opencv/4.7.0_1/include/opencv4
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "opencv2/imgcodecs.hpp"


void task4(int argc, char** argv) {

    cv::Mat gray;
    std::string str = argv[1];
    cv::Mat img = cv::imread(argv[1]);

    cv::cvtColor(img, gray, cv::COLOR_BGR2GRAY);
    cv::medianBlur(gray, gray, 5);

    std::vector<cv::Vec3f> circles;
    HoughCircles(gray, circles, cv::HOUGH_GRADIENT, 2, gray.rows/10, 750, 25, 0, 20 );

    for( size_t i = 0; i < circles.size(); i++ ) {

        cv::Vec3i c = circles[i];
        cv::Point center = cv::Point(c[0], c[1]);
        int radius = c[2];
        cv::circle(img, center, radius, cv::Scalar(0,255,0), cv::FILLED, cv::LINE_AA);
    }


    cv::namedWindow("detected circles");
    cv::imshow("detected circles", img);
    cv::waitKey(0);
    cv::destroyAllWindows();
}