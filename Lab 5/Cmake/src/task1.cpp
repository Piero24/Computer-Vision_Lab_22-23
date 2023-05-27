// task1.cpp
// g++ -std=c++11 -o task1 task1.cpp -I/usr/local/include/opencv4/ -lopencv_core -lopencv_highgui -lopencv_imgcodecs -lopencv_imgproc
// ./task1 Asphalt-1.png
// ./task1 Asphalt-1.png Asphalt-2.png Asphalt-3.png


//
// I Have follow the third method at this link for this ex
// https://machinelearningknowledge.ai/image-segmentation-in-python-opencv/
//
//


#include <iostream>
// /usr/local/Cellar/opencv/4.7.0_1/include/opencv4
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "../include/funcTask1.h"


void task1(int argc, char** argv) {

    for (int i = 1; i < argc; i++) {

        std::string str = argv[i];

        if (str.substr(str.size() - 4) == ".jpg" || str.substr(str.size() - 4) == ".png") {

            str.erase(str.size() - 4);
        }

        cv::Mat img = cv::imread(argv[i]);

        cv::Mat mask;
        mask = thresholdOtsu(img);

        cv::Mat finalImg;
        finalImg = filter_image(img, mask);

        cv::namedWindow(str);
        cv::imshow(str, finalImg);
        cv::destroyAllWindows();

    }
    cv::waitKey(0);
}