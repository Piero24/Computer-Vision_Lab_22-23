// task5.cpp
// g++ -std=c++11 -o ./tasks/task5 ./tasks/task5.cpp -I/usr/local/include/opencv4/ -lopencv_core -lopencv_highgui -lopencv_imgcodecs -lopencv_imgproc
// ./tasks/task5 ./images/image.jpg

#include <iostream>
#include <vector>
// /usr/local/Cellar/opencv/4.7.0_1/include/opencv4
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

int main(int argc, char** argv) {


    cv::Mat img = cv::imread(argv[1]);
    cv::Mat image_grayscale;
    cv::cvtColor(img, image_grayscale, cv::COLOR_BGR2GRAY);

    cv::Mat equalized_img;
    cv::equalizeHist(image_grayscale, equalized_img);

    std::vector<cv::Mat> bgr_planes;
    split(equalized_img, bgr_planes);

    int histSize = 256;
    float range[] = { 0, 256 }; //the upper boundary is exclusive
    const float* histRange[] = { range };
    bool uniform = true, accumulate = false;

    cv::Mat gray_hist;
    cv::calcHist(&bgr_planes[0], 1, 0, cv::Mat(), gray_hist, 1, &histSize, histRange, uniform, accumulate);

    int hist_w = 512, hist_h = 400;
    int bin_w = cvRound((double) hist_w/histSize);
    cv::Mat histImage(hist_h, hist_w, CV_8UC3, cv::Scalar( 0,0,0));

    cv::normalize(gray_hist, gray_hist, 0, histImage.rows, cv::NORM_MINMAX, -1, cv::Mat());

    for( int i = 1; i < histSize; i++ ) {
        line(histImage, cv::Point( bin_w*(i-1), hist_h - cvRound(gray_hist.at<float>(i-1))),
              cv::Point( bin_w*(i), hist_h - cvRound(gray_hist.at<float>(i))),
              cv::Scalar( 0, 0, 255), 2, 8, 0);
    }

    imwrite( "equalized_image.jpg", equalized_img);
    imwrite( "histogram_eq_of_the_image.jpg.jpg", histImage);

    cv::imshow("Gray image", image_grayscale);
    cv::imshow("Equalized Demo", equalized_img);
    cv::imshow("Histogram Equalized Demo", histImage);
    cv::waitKey(0);

    return 0;
}