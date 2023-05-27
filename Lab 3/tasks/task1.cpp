// task1.cpp
// g++ -std=c++11 -o ./tasks/task1 ./tasks/task1.cpp -I/usr/local/include/opencv4/ -lopencv_core -lopencv_highgui -lopencv_imgcodecs -lopencv_imgproc
// ./tasks/task1 ./images/robocup.jpg

#include <iostream>
// /usr/local/Cellar/opencv/4.7.0_1/include/opencv4
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

int main(int argc, char** argv) {

    std::string str = argv[1];

    if (str.substr(str.size() - 4) == ".jpg" || str.substr(str.size() - 5) == ".jpeg") {

        str.erase(str.size() - 4);
    }


    cv::Mat img = cv::imread(argv[1]);

    cv::namedWindow(str);
    cv::imshow(str, img);
    cv::waitKey(0);

    return 0;
}