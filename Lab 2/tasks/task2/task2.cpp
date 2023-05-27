// task2.cpp
// g++ -std=c++11 -c -o ./tasks/task2/maxFilter.o ./tasks/task2/maxFilter.cpp -I/usr/local/include/opencv4/
// ar rcs libmaxFilter.a ./tasks/task2/maxFilter.o
// g++ -std=c++11 -c -o ./tasks/task2/minFilter.o ./tasks/task2/minFilter.cpp -I/usr/local/include/opencv4/
// ar rcs libminFilter.a ./tasks/task2/minFilter.o
// g++ -std=c++11 -o ./tasks/task_2 ./tasks/task2/task2.cpp -I/usr/local/include/opencv4/ -lopencv_core -lopencv_highgui -lopencv_imgcodecs -lopencv_imgproc -L. -lmaxFilter -lminFilter

// ./tasks/task_2 image_grayscale.jpg

#include <iostream>
// /usr/local/Cellar/opencv/4.7.0_1/include/opencv4
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include "maxFilter.h"
#include "minFilter.h"

cv::Mat maxFilter(cv::Mat img, int kernelSize);
cv::Mat minFilter(cv::Mat img, int kernelSize);


int main(int argc, char** argv) {


    cv::Mat img = cv::imread(argv[1]);

    int dimKernel;
    std::cout << "Type a number for the kernel size (MUST BE ODD. 5 is the recommended value.): ";
    std::cin >> dimKernel;

    cv::Mat maxImage = maxFilter(img, dimKernel);
    cv::Mat minImage = maxFilter(img, dimKernel);

    imwrite( "image_max_filter_" + std::to_string(dimKernel) + ".jpg", maxImage);
    imwrite( "image_min_filter_" + std::to_string(dimKernel) + ".jpg", minImage);

    //std::cout << "Number of rows: " << img.rows << "\n";
    //std::cout << "Number of columns: " << img.cols << "\n";

    cv::namedWindow("Max Filter");
    cv::imshow("Max Filter", maxImage);
    cv::namedWindow("Min Filter");
    cv::imshow("Min Filter", minImage);
    cv::waitKey(0);

    return 0;
}
