// task4.cpp
// g++ -std=c++11 -o ./tasks/task4 ./tasks/task4.cpp -I/usr/local/include/opencv4/ -lopencv_core -lopencv_highgui -lopencv_imgcodecs
// ./tasks/task4 ./images/Lena_color.jpg
// ./tasks/task4 ./images/Lena_grayscale.jpg
// ./tasks/task4 ./images/DL_gurus.jpg

#include <iostream>
// import vector for the list
#include <vector>
// /usr/local/Cellar/opencv/4.7.0_1/include/opencv4
#include <opencv2/highgui.hpp>

int funcOneChannel(cv::Mat img);


int main(int argc, char** argv) {

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
    funcOneChannel(img);

    cv::namedWindow("Example 1");
    cv::imshow("Example 1", img);
    char keyOutput = cv::waitKey(0);
    std::cout << "The output returned from waitKey(0) is: " << keyOutput << "\n";

    return 0;
}

// Task
// Function that return the image without the selected channel
int funcOneChannel(cv::Mat img) {

    if (img.channels() == 3) {

        // Define the list of the couple we want to remove
        std::vector<std::vector<int>> list = {{0, 1}, {0, 2}, {1, 2}};

        for (auto couple : list) {

            cv::Mat chans[3]; 
            cv::Mat newImg;
            // split the channels in order to manipulate them
            split(img, chans);

            // First channel to remove
            chans[couple[0]]=cv::Mat::zeros(img.rows, img.cols, CV_8UC1);
            // Second channel to remove
            chans[couple[1]]=cv::Mat::zeros(img.rows, img.cols, CV_8UC1);

            merge(chans, 3, newImg);
            cv::namedWindow("Example 1");
            cv::imshow("Example 1", newImg);
            char keyOutput = cv::waitKey(0);

        }        
    }  

    return 0;
}