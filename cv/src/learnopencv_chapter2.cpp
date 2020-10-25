#include "learnopencv.h"
#include "opencv2/highgui/highgui.hpp"

int showimage(int argc, char *argv[]) {
    cv::Mat img = cv::imread(argv[1], -1);
    if (img.empty()) {
        return -1;
    }
    cv::namedWindow("Example1", cv::WINDOW_AUTOSIZE);
    cv::imshow("Example1", img);
    cv::waitKey(0);
    cv::destroyWindow("Example");
    return 0;
}

int showvideo(int argc, char *argv[]) {
    cv::namedWindow("Example2", cv::WINDOW_AUTOSIZE);
    cv::VideoCapture cap;
    cap.open(argv[1]);
    cv::Mat frame;
    for (;;) {
        cap >> frame;
        if (frame.empty()) {
            break;
        }
        cv::imshow("Example3", frame);
        if (cv::waitKey(33) >= 0) {
            break;
        }
    }
    return 0;
}