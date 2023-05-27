// task1.cpp
// g++ -std=c++11 -o ./tasks/task1 ./tasks/task1.cpp -I/usr/local/include/opencv4/ -lopencv_core -lopencv_highgui -lopencv_imgcodecs -lopencv_imgproc
// ./tasks/task1 ./images/image.jpg

#include <iostream>
// /usr/local/Cellar/opencv/4.7.0_1/include/opencv4
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

int main(int argc, char** argv) {


    cv::Mat img = cv::imread(argv[1]);
    cv::Mat image_grayscale;
    cv::cvtColor(img, image_grayscale, cv::COLOR_BGR2GRAY);

    cv::imwrite( "image_grayscale.jpg", image_grayscale);

    cv::namedWindow("Example 1");
    cv::imshow("Example 1", image_grayscale);
    cv::waitKey(0);

    return 0;
}