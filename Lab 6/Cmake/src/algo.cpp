#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <algorithm>
#include "../include/funcTask1.h"


// Definisci una funzione di confronto per le corrispondenze
bool compareMatches(const cv::DMatch& match1, const cv::DMatch& match2) {
    return match1.distance < match2.distance;
}
