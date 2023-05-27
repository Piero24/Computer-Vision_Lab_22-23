// task3.cpp
// g++ -std=c++11 -o ./tasks/task3 ./tasks/task3.cpp -I/usr/local/include/opencv4/ -lopencv_core -lopencv_highgui -lopencv_imgcodecs
// ./tasks/task3 ./images/Lena_color.jpg
// ./tasks/task3 ./images/Lena_grayscale.jpg
// ./tasks/task3 ./images/DL_gurus.jpg

#include <iostream>
// /usr/local/Cellar/opencv/4.7.0_1/include/opencv4
#include <opencv2/highgui.hpp>

// function declaration
int funcRemChannel(cv::Mat img, int num);

int main(int argc, char** argv) {

    int selectedChannel; 

    if (argc < 2) {

        std::cout << "argc have less then 2 param\n";
        return 0;

    }

    cv::Mat img = cv::imread(argv[1]);
    if (img.data == NULL) {

        std::cout << "The image name are wrong\n";
        return 0;

    }
    //std::cout << "The number of channel of this image is: " << img.channels() << "\n";

    // Type a number and press enter
    std::cout << "Type the channel you want to remove: ";
    std::cin >> selectedChannel; // Get user input from the keyboard
    funcRemChannel(img, selectedChannel);

    cv::namedWindow("Example 1");
    cv::imshow("Example 1", img);
    char keyOutput = cv::waitKey(0);
    std::cout << "The output returned from waitKey(0) is: " << keyOutput << "\n";

    return 0;
}

// Task
// Function that in output one image for each channel
int funcRemChannel(cv::Mat img, int num) {

    if (img.channels() == 3) {

        cv::Mat chans[3]; 

        // split the channels in order to manipulate them
        split(img, chans);

        // By default opencv put channels in BGR order
        if (num == 0) {
            // Blue channel is set to 0
            chans[0]=cv::Mat::zeros(img.rows, img.cols, CV_8UC1);

        } else if (num == 1) {
            // Green channel is set to 0
            chans[1]=cv::Mat::zeros(img.rows, img.cols, CV_8UC1);

        } else if (num == 2) {
            // Red channel is set to 0
            chans[2]=cv::Mat::zeros(img.rows, img.cols, CV_8UC1);

        }

        merge(chans, 3, img);
        cv::namedWindow("Example 1");
        cv::imshow("Example 1", img);
        char keyOutput = cv::waitKey(0);        
    }  

    return 0;
}