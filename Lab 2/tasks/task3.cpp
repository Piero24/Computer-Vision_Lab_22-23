// task3.cpp
// g++ -std=c++11 -o ./tasks/task3 ./tasks/task3.cpp -I/usr/local/include/opencv4/ -lopencv_core -lopencv_highgui -lopencv_imgcodecs -lopencv_imgproc
// ./tasks/task3 image_grayscale.jpg

#include <iostream>
// /usr/local/Cellar/opencv/4.7.0_1/include/opencv4
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>



int main(int argc, char** argv) {


    cv::Mat img = cv::imread(argv[1]);

    int dimKernel;
    std::cout << "Type a number for the kernel size (MUST BE ODD. 5 is the recommended value.): ";
    std::cin >> dimKernel;

    cv::Mat medianImage;
    cv::Mat gaussianImage;

    cv::medianBlur(img, medianImage, dimKernel);
    cv::GaussianBlur(img, gaussianImage, cv::Size(dimKernel, dimKernel), 0, 0);

    imwrite( "image_median_filter_" + std::to_string(dimKernel) + ".jpg", medianImage);
    imwrite( "image_gaussian_filter_" + std::to_string(dimKernel) + ".jpg", gaussianImage);

    //std::cout << "Number of rows: " << img.rows << "\n";
    //std::cout << "Number of columns: " << img.cols << "\n";

    cv::namedWindow("Median Filter");
    cv::imshow("Median Filter", medianImage);
    cv::namedWindow("Gaussian Filter");
    cv::imshow("Gaussian Filter", gaussianImage);
    cv::waitKey(0);

    return 0;
}

