#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "../include/Tasks.h"
#include "../include/funcTask1.h"

int main(int argc, char** argv) {

    char in;
    std::cout << "The program will perform all 3 different tasks on the images given in input, therefore it is recommended to execute it in this way:" << std::endl;
    std::cout << "program_name Asphalt-1.png Asphalt-2.png Asphalt-3.png" << std::endl;
    std::cout << "program_name street_scene.png" << std::endl;
    std::cout << "program_name robocup.jpg \n" << std::endl;

    std::cout << "Press enter to start:" << std::endl;
    std::cin.get(in);

    std::cout << "Task 1 press any key to continue." << std::endl;
    task1(argc, argv);

    std::cout << "Task 2 press any key to continue." << std::endl;
    task2(argc, argv);

    std::cout << "Task 3 press any key to continue." << std::endl;
    task3(argc, argv);

    std::cout << "Tasks terminated." << std::endl;

    return 0;
}
