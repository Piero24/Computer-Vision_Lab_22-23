// task2.cpp
// g++ -std=c++11 -o ./tasks/task2 ./tasks/task2.cpp -I/usr/local/include/opencv4/ -lopencv_core -lopencv_highgui -lopencv_imgcodecs
// ./tasks/task2 ./images/Lena_color.jpg

#include <iostream>
// /usr/local/Cellar/opencv/4.7.0_1/include/opencv4
#include <opencv2/highgui.hpp>
int main(int argc, char** argv) {

    if (argc < 2) {

        std::cout << "argc have less then 2 param\n";
        return 0;

    }

    cv::Mat img = cv::imread(argv[1]);
    if (img.data == NULL) {

        std::cout << "The image name are wrong\n";
        return 0;

    }
    // First task2
    // Test: ./tasks/task2 ./images/Lena_color.jpg
    std::cout << "The number of channel of this image is: " << img.channels() << "\n";

    cv::namedWindow("Example 1");
    cv::imshow("Example 1", img);
    char keyOutput = cv::waitKey(0);
    // Second task2
    // Test: ./tasks/task2 ./images/Lena_color.jpg
    std::cout << "The output returned from waitKey(0) is: " << keyOutput << "\n";

    return 0;
}