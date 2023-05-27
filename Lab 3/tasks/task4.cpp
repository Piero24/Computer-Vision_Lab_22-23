// task1.cpp
// g++ -std=c++11 -o ./tasks/task4 ./tasks/task4.cpp -I/usr/local/include/opencv4/ -lopencv_core -lopencv_highgui -lopencv_imgcodecs -lopencv_imgproc
// ./tasks/task4 ./images/robocup.jpg

#include <iostream>
// /usr/local/Cellar/opencv/4.7.0_1/include/opencv4
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>


void onMouse( int event, int x, int y, int f, void* userdata);


int main(int argc, char** argv) {

    std::string str = argv[1];

    if (str.substr(str.size() - 4) == ".jpg" || str.substr(str.size() - 5) == ".jpeg") {

        str.erase(str.size() - 4);
    }


    cv::Mat img = cv::imread(argv[1]);

    cv::namedWindow(str);
    cv::imshow(str, img);
    cv::setMouseCallback(str, onMouse, (void*)&img);

    cv::waitKey(0);
    return 0;
}

void onMouse(int event, int x, int y, int f, void* userdata) {

    if (event == cv::EVENT_LBUTTONDOWN) {

        int threshold = 80;
        
        cv::Mat image = *static_cast<cv::Mat*>(userdata);
        cv::Mat image_out = image.clone();
        cv::Mat mask_image = cv::Mat::zeros(image.size(), image.type());

        // Preventing segfaults for looking over the image boundaries
        if (y > image_out.rows || x > image_out.cols) {
            return;
        }

        cv::Vec3b val = image.at<cv::Vec3b>(x, y);
        //std::cout << "the BGR color is: " << val << std::endl;

        for (int col = 0; col <= image.cols -1; col++) {
            for (int row = 0; row <= image.rows -1; row++) {

                cv::Vec3b valToCheck = image.at<cv::Vec3b>(row, col);
                if (((valToCheck[0] < (val[0] + threshold)) && (valToCheck[0] > (val[0] - threshold))) && 
                ((valToCheck[1] < (val[1] + threshold)) && (valToCheck[1] > (val[1] - threshold))) && 
                ((valToCheck[2] < (val[2] + threshold)) && (valToCheck[2] > (val[2] - threshold)))) {
                    
                    mask_image.at<cv::Vec3b>(row, col) = cv::Vec3b(255, 255, 255);
                } 
            }
        }

        imwrite( "mask_image.jpg", mask_image);
        
        cv::namedWindow("mask");
        cv::imshow("mask", mask_image);
    }
}