// task3.cpp
// g++ -std=c++11 -o task3 task3.cpp -I/usr/local/include/opencv4/ -lopencv_core -lopencv_highgui -lopencv_imgcodecs -lopencv_imgproc
// ./task3 robocup.jpg


//
// I Have follow the fourth method at this link for this ex (Color Masking)
// https://machinelearningknowledge.ai/image-segmentation-in-python-opencv/
//
//

#include <iostream>
// /usr/local/Cellar/opencv/4.7.0_1/include/opencv4
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

void task3(int argc, char** argv) {

    std::string str = argv[1];

    if (str.substr(str.size() - 4) == ".jpg" || str.substr(str.size() - 4) == ".png") {

        str.erase(str.size() - 4);
    }

    cv::Mat img = cv::imread(argv[1]);
    cv::Mat orange_mask;
    cv::inRange(img, cv::Scalar(0, 60, 90), cv::Scalar(65, 190, 255), orange_mask);

    std::vector<cv::Vec3f> circles;
    cv::HoughCircles(orange_mask, circles, cv::HOUGH_GRADIENT, 2, orange_mask.rows/10, 850, 63, 0, 50);

    for( size_t i = 0; i < circles.size(); i++ ) {

        std::vector<cv::Point> relevantPoints;
        std::vector<std::vector<cv::Point>> edges;

        cv::Vec3i c = circles[i];
        int centerRow = c[0];
        int centerCol = c[1];
        int radius = c[2];
        int treshold = radius + 20;

        cv::Point A = cv::Point(centerRow - treshold, centerCol - treshold);
        cv::Point B = cv::Point(centerRow - treshold, centerCol + treshold);
        cv::Point C = cv::Point(centerRow + treshold, centerCol + treshold);
        cv::Point D = cv::Point(centerRow + treshold, centerCol - treshold);

        relevantPoints.push_back(A);
        relevantPoints.push_back(B);
        relevantPoints.push_back(C);
        relevantPoints.push_back(D);

        edges.push_back(relevantPoints);
        drawContours(orange_mask, edges, 0, cv::Scalar(0, 0, 0), cv::FILLED, cv::LINE_AA);
    }

    //cv::Mat non_orange_mask = ~orange_mask;

    cv::Mat finalImg(img.size(), img.type());
    //cv::bitwise_and(img, img, finalImg, orange_mask);

    for (int row = 0; row < img.rows; row++) {
        for (int col = 0; col < img.cols; col++) {
            if (orange_mask.at<uchar>(row, col) > 0) {
                finalImg.at<cv::Vec3b>(row, col) = img.at<cv::Vec3b>(row, col);
            }
            else {
                finalImg.at<cv::Vec3b>(row, col) = cv::Vec3b(0, 0, 0);
            }
        }
    }

    //cv::imwrite("RobotImg.png", finalImg);
                
    cv::namedWindow(str);
    cv::imshow(str, finalImg);
    cv::waitKey(0);
    cv::destroyAllWindows();

}


