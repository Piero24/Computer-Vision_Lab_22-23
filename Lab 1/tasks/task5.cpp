// task5.cpp
// g++ -std=c++11 -o ./tasks/task5 ./tasks/task5.cpp -I/usr/local/include/opencv4/ -lopencv_core -lopencv_highgui -lopencv_imgcodecs
// ./tasks/task5

#include <iostream>
// /usr/local/Cellar/opencv/4.7.0_1/include/opencv4
#include <opencv2/highgui.hpp>

// Since the first two images have the same dimensions and the same goes for the 
// second 2, it is enough to use only one cycle for each pair of images (So as to 
// improve the complexity) Alternatively, just uncomment the code below and comment 
// out a portion of the one present in the loops to separate each image into a 
// well-defined piece of code.

int main(void) {
    // Create two images of size 256x256 with one channel
    cv::Mat image1(256, 256, CV_8UC1);
    cv::Mat image2(256, 256, CV_8UC1);

    // Create a vertical gradient in the first image
    for (int y = 0; y < image1.rows; y++) {
        for (int x = 0; x < image1.cols; x++) {
            image1.at<uchar>(y, x) = y;
             image2.at<uchar>(y, x) = x;
            
        }
    }

    // Create a vertical gradient in the first image
    for (int y = 0; y < image2.rows; y++) {
        for (int x = 0; x < image2.cols; x++) {
            image2.at<uchar>(y, x) = x;
            
        }
    }

    // Create two images of size 300x300 with one channel
    cv::Mat image3(300, 300, CV_8UC1);
    cv::Mat image4(300, 300, CV_8UC1);

    // Create a chessboard with squares of size 20 pixels in the third image
    for (int y = 0; y < image3.rows; y++) {
        for (int x = 0; x < image3.cols; x++) {

            int value = ((x / 20) + (y / 20)) % 2;
            image3.at<uchar>(y, x) = value * 255;

            int value2 = ((x / 50) + (y / 50)) % 2;
            image4.at<uchar>(y, x) = value2 * 255;
        }
    }

    // Create a chessboard with squares of size 50 pixels in the fourth image
    // for (int y = 0; y < image4.rows; y++) {
    //     for (int x = 0; x < image4.cols; x++) {
    //         int value = ((x / 50) + (y / 50)) % 2;
    //         image4.at<uchar>(y, x) = value * 255;
    //     }
    // }

    // Display the four images
    cv::imshow("Vertical Gradient", image1);
    cv::imshow("Horizontal Gradient", image2);
    cv::imshow("Chessboard 20x20", image3);
    cv::imshow("Chessboard 50x50", image4);
    
    cv::waitKey(0);

    return 0;

}