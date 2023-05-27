// task3.cpp
// g++ -std=c++11 -o task3 task3.cpp -I/usr/local/include/opencv4/ -lopencv_core -lopencv_highgui -lopencv_imgcodecs -lopencv_imgproc
// ./task3 street_scene.png

#include <iostream>
// /usr/local/Cellar/opencv/4.7.0_1/include/opencv4
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "opencv2/imgcodecs.hpp"


void task3(int argc, char** argv) {

    cv::Mat cannyImg;
    cv::Mat colorImg;

    std::string str = argv[1];

    cv::Mat img = cv::imread(argv[1]);

    cv::Canny(img, cannyImg, 897, 662);
    // Copy edges to the images that will display the results in BGR
    cv::cvtColor(cannyImg, colorImg, cv::COLOR_GRAY2BGR);

    // Standard Hough Line Transform
    std::vector<cv::Vec2f> lines; // will hold the results of the detection
    HoughLines(cannyImg, lines, 1, CV_PI/180, 97, 0, 0); // runs the actual detection

    std::vector<cv::Point> linesPoints;
    std::vector<cv::Point> relevantPoints;

    // Draw the lines
    for(size_t i = 0; i < lines.size(); i++) {
        
        float rho = lines[i][0];
        float theta = lines[i][1];
        cv::Point pt1, pt2;
        double a = cos(theta), b = sin(theta);
        double x0 = a*rho, y0 = b*rho;
        pt1.x = cvRound(x0 + 1000*(-b));
        pt1.y = cvRound(y0 + 1000*(a));
        pt2.x = cvRound(x0 - 1000*(-b));
        pt2.y = cvRound(y0 - 1000*(a));

        float angle = atan2(pt1.x - pt2.x, pt1.y - pt2.y) * 180.0 / CV_PI;

        if (!(angle > -132 && angle < -46.9)) {

            cv::line(colorImg, pt1, pt2, cv::Scalar(0,0,255), 2, cv::LINE_AA);
            cv::LineIterator it(colorImg, pt1, pt2, 8);

            for (int i = 0; i < it.count; i++, ++it) {

                cv::Point pt3 = it.pos();
                auto it = std::find(linesPoints.begin(), linesPoints.end(), pt3);

                if ((pt3.y >= colorImg.rows - 1) || it != linesPoints.end()) {

                    relevantPoints.push_back(pt3);
                    
                    if (it != linesPoints.end()) {

                        relevantPoints.push_back(pt3);

                    }

                } else {

                    linesPoints.push_back(pt3);

                }
            }
        }
    }

    std::vector<std::vector<cv::Point>> edges;
    edges.push_back(relevantPoints);
    drawContours(img, edges, 0, cv::Scalar(0, 0, 255), cv::FILLED, cv::LINE_AA);

    // Show results
    // -- REMOVE THE COMMENT IF YOU WANT TO SEE THE LINES --
    //cv::namedWindow("Lines");
    //cv::imshow("Lines", colorImg);
    cv::namedWindow("Detected Lines (in red) - Probabilistic Line Transform");
    cv::imshow("Detected Lines (in red) - Probabilistic Line Transform", img);
    cv::waitKey(0);
    cv::destroyAllWindows();
}