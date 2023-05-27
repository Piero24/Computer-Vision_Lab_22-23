// task1.cpp
// g++ -std=c++11 -o ./tasks/task3 ./tasks/task3.cpp -I/usr/local/include/opencv4/ -lopencv_core -lopencv_highgui -lopencv_imgcodecs -lopencv_imgproc
// ./tasks/task3 ./images/robocup.jpg

#include <iostream>
// /usr/local/Cellar/opencv/4.7.0_1/include/opencv4
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>


void onMouse( int event, int x, int y, int f, void* userdata);

#define NEIGHBORHOOD_Y 9
#define NEIGHBORHOOD_X 9

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
        
        cv::Mat image = *static_cast<cv::Mat*>(userdata);
        cv::Mat image_out = image.clone();

        // Preventing segfaults for looking over the image boundaries
        if (y + NEIGHBORHOOD_Y > image_out.rows || x + NEIGHBORHOOD_X > image_out.cols) {
            return;
        }

        cv::Rect rect(x, y, NEIGHBORHOOD_X, NEIGHBORHOOD_Y);
        cv::Scalar mean = cv::mean(image_out(rect));
        std::cout << "the mean BGR color of the 9x9 is: " << mean << std::endl;
    }

}