// task2.cpp
// g++ -std=c++11 -o task2 task2.cpp -I/usr/local/include/opencv4/ -lopencv_core -lopencv_highgui -lopencv_imgcodecs -lopencv_imgproc
// ./task2 street_scene.png

#include <iostream>
// /usr/local/Cellar/opencv/4.7.0_1/include/opencv4
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>


void task2(int argc, char** argv) {

    std::string str = argv[1];

    if (str.substr(str.size() - 4) == ".jpg" || str.substr(str.size() - 4) == ".png") {

        str.erase(str.size() - 4);
    }

    cv::Mat img = cv::imread(argv[1]);

    cv::Mat blurredImg;
    cv::Mat kernel2 = cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(25, 25));
    cv::erode(img, blurredImg, kernel2);

    cv::GaussianBlur(blurredImg, blurredImg, cv::Size(3, 3), 0);

    // Convert the image into a matrix of pixel (float)
    cv::Mat points(img.rows * img.cols, 3, CV_32F);

    for(int y = 0; y < img.rows; y++) {
        for(int x = 0; x < img.cols; x++) {
            for(int z = 0; z < 3; z++) {

                points.at<float>(y + x * img.rows, z) = blurredImg.at<cv::Vec3b>(y,x)[z];
            }
        }
    }

    //Number of clusters
    int K = 3;
    // Output vector
    cv::Mat labels;
    cv::Mat centers;

    cv::kmeans(points, K, labels,
        cv::TermCriteria(cv::TermCriteria::EPS + cv::TermCriteria::COUNT, 10, 1.0), 3, cv::KMEANS_PP_CENTERS, centers);

    // Assigns a color to pixels based on the cluster they belong to
    cv::Mat new_image(img.size(), img.type());

    for(int x = 0; x < img.cols; x++) {
        for(int y = 0; y < img.rows; y++) {

            //std::cout << labels << std::endl;
            int cluster_idx = labels.at<int>(y + x * img.rows, 0);
            new_image.at<cv::Vec3b>(y,x)[0] = centers.at<float>(cluster_idx, 0);
            new_image.at<cv::Vec3b>(y,x)[1] = centers.at<float>(cluster_idx, 1);
            new_image.at<cv::Vec3b>(y,x)[2] = centers.at<float>(cluster_idx, 2);
        }
    }

    // BGR (Blue-Green-Red)
    cv::Vec3b asphalt(90, 93, 82);
    cv::Vec3b other(15, 23, 14);
    cv::Vec3b sky(250, 191, 113);

    int treshold = 15;
    int treshold2 = 5;

    for(int x = 0; x < img.cols; x++) {
        for(int y = 0; y < img.rows; y++) {

            cv::Vec3b current = new_image.at<cv::Vec3b>(y, x);

            if (y > 0) {

                cv::Vec3b previous = new_image.at<cv::Vec3b>(y - 1, x);

                if ((previous[0] < sky[0] + treshold2) && (previous[0] > sky[0] - treshold) && 
                    (previous[1] < sky[1] + treshold) && (previous[1] > sky[1] - treshold) && 
                    (previous[2] < sky[2] + treshold) && (previous[2] > sky[2] - treshold)) {

                    if ((current[0] < asphalt[0] + treshold) && (current[0] > asphalt[0] - treshold) && 
                        (current[1] < asphalt[1] + treshold) && (current[1] > asphalt[1] - treshold) && 
                        (current[2] < asphalt[2] + treshold) && (current[2] > asphalt[2] - treshold)) {

                        //std::cout << "Qui" << std::endl;
                        new_image.at<cv::Vec3b>(y, x) = sky;
                            

                    }
                }

            } else if (y < 1) {

                if ((current[0] < asphalt[0] + treshold) && (current[0] > asphalt[0] - treshold) && 
                    (current[1] < asphalt[1] + treshold) && (current[1] > asphalt[1] - treshold) && 
                    (current[2] < asphalt[2] + treshold) && (current[2] > asphalt[2] - treshold)) {

                    new_image.at<cv::Vec3b>(y, x) = cv::Vec3b(250, 191, 113);
                        

                }
            }
            
        }
    }

    //cv::imwrite("MyImage.png", new_image);

    cv::namedWindow(str);
    cv::imshow(str, new_image);

    cv::waitKey(0);
    cv::destroyAllWindows();
}
