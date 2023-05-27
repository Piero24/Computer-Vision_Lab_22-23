// task4.cpp
// g++ -std=c++11 -o ./tasks/task4 ./tasks/task4.cpp -I/usr/local/include/opencv4/ -lopencv_core -lopencv_highgui -lopencv_imgcodecs -lopencv_imgproc
// ./tasks/task4 ./images/image.jpg

#include <iostream>
#include <vector>
// /usr/local/Cellar/opencv/4.7.0_1/include/opencv4
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

int main(int argc, char** argv) {


    cv::Mat img = cv::imread(argv[1]);

    std::vector<cv::Mat> bgr_planes;
    split(img, bgr_planes);

    int histSize = 256;
    float range[] = { 0, 256 }; //the upper boundary is exclusive
    const float* histRange[] = { range };
    bool uniform = true, accumulate = false;

    cv::Mat b_hist, g_hist, r_hist;
    cv::calcHist( &bgr_planes[0], 1, 0, cv::Mat(), b_hist, 1, &histSize, histRange, uniform, accumulate );
    cv::calcHist( &bgr_planes[1], 1, 0, cv::Mat(), g_hist, 1, &histSize, histRange, uniform, accumulate );
    cv::calcHist( &bgr_planes[2], 1, 0, cv::Mat(), r_hist, 1, &histSize, histRange, uniform, accumulate );

    int hist_w = 512, hist_h = 400;
    int bin_w = cvRound((double) hist_w/histSize);
    cv::Mat histImage(hist_h, hist_w, CV_8UC3, cv::Scalar( 0,0,0));

    cv::normalize(b_hist, b_hist, 0, histImage.rows, cv::NORM_MINMAX, -1, cv::Mat() );
    cv::normalize(g_hist, g_hist, 0, histImage.rows, cv::NORM_MINMAX, -1, cv::Mat() );
    cv::normalize(r_hist, r_hist, 0, histImage.rows, cv::NORM_MINMAX, -1, cv::Mat() );

    for( int i = 1; i < histSize; i++ )
    {
        line(histImage, cv::Point( bin_w*(i-1), hist_h - cvRound(b_hist.at<float>(i-1))),
              cv::Point( bin_w*(i), hist_h - cvRound(b_hist.at<float>(i))),
              cv::Scalar( 255, 0, 0), 2, 8, 0);
        line(histImage, cv::Point( bin_w*(i-1), hist_h - cvRound(g_hist.at<float>(i-1))),
              cv::Point( bin_w*(i), hist_h - cvRound(g_hist.at<float>(i))),
              cv::Scalar( 0, 255, 0), 2, 8, 0);
        line(histImage, cv::Point( bin_w*(i-1), hist_h - cvRound(r_hist.at<float>(i-1))),
              cv::Point( bin_w*(i), hist_h - cvRound(r_hist.at<float>(i))),
              cv::Scalar( 0, 0, 255), 2, 8, 0);
    }

    imwrite( "histogram_of_the_image.jpg", histImage);

    cv::imshow("Source image", img);
    cv::imshow("calcHist Demo", histImage);
    cv::waitKey(0);

    return 0;
}