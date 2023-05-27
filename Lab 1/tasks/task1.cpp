// task1.cpp
// g++ -std=c++11 -o ./tasks/task1 ./tasks/task1.cpp -I/usr/local/include/opencv4/ -lopencv_core -lopencv_highgui -lopencv_imgcodecs
// ./tasks/task1 ./images/Lena_color.jpg
// ./tasks/task1 ./images/Lena_grayscale.jpg
// ./tasks/task1 ./images/DL_gurus.jpg

#include <iostream>
// /usr/local/Cellar/opencv/4.7.0_1/include/opencv4
#include <opencv2/highgui.hpp>
int main(int argc, char** argv) {

    // First task1
    // Test: ./tasks/task1 ./images/Lena_color.jpg
    if (argc < 2) {

        std::cout << "argc have less then 2 param\n";
        return 0;

    }

    cv::Mat img = cv::imread(argv[1]);
    // Second task1
    // Test: ./tasks/task1 ./images/Lenacolor.jpg
    if (img.data == NULL) {

        std::cout << "The image name are wrong\n";
        return 0;

    }
    cv::namedWindow("Example 1");
    cv::imshow("Example 1", img);
    cv::waitKey(0);

    return 0;
}