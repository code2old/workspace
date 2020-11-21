#include "learnopencv.h"

#include "opencv2/opencv.hpp"
#include <iostream>
#include <vector>

using namespace std;

void sum_rgb(const cv::Mat &src, cv::Mat &dst) {
    vector<cv::Mat> planes;
    cv::split(src, planes);
    cv::Mat b = planes[0];
    cv::Mat g = planes[1];
    cv::Mat r = planes[2];
    cv::Mat s;

    cv::addWeighted(r, 1. / 3., g, 1. / 3., 0.0, s);
    cv::addWeighted(s, 1., b, 1. / 3., 0.0, s);

    cv::threshold(s, dst, 100, 100, cv::THRESH_TRUNC);
}

static void help() {
    cout << "Call: ./exe faceScene.jpg" << endl;
    cout << "Show use of alpha blending (addWeight) and threshold" << endl;
}

int cvthreshold(int argc, char *argv[]) {
    help();

    if (argc < 2) {
        cout << "specify input image" << endl;
        return -1;
    }
    cv::Mat src = cv::imread(argv[1]);
    cv::Mat dst;
    if (src.empty()) {
        cout << "can't not load " << argv[1] << endl;
        return 0;
    }
    sum_rgb(src, dst);
    cv::imshow(argv[1], dst);
    cv::waitKey(0);
    cv::destroyWindow(argv[1]);
    return 0;
}

int cvadapterthreshold(int argc, char *argv[]) {
    if (argc != 7) {
        cout << "Usage: " << argv[0] << " fixed_threshold invert(0=off|1=on) "
            "adaptive_tpye(0=mean|1=gaussian) block_size offset image\n"
            "Example: " << argv[0] << " 100 1 0 15 10 fruits.jpg\n";
        return -1;
    }
    double fixed_threshold = (double)atof(argv[1]);
    int threshold_type = atoi(argv[2]) ? cv::THRESH_BINARY : cv::THRESH_BINARY_INV;
    int adaptive_method = atoi(argv[3]) ? cv::ADAPTIVE_THRESH_MEAN_C : cv::ADAPTIVE_THRESH_GAUSSIAN_C;
    int block_size = atoi(argv[4]);
    double offset = (double)atof(argv[5]);
    cv::Mat Igray = cv::imread(argv[6], cv::IMREAD_GRAYSCALE);

    if (Igray.empty()) {
        cout << "Can not load " << argv[6] << endl;
        return -1;
    }
    cv::Mat It, Iat;
    cv::threshold(Igray, It, fixed_threshold, 255, threshold_type);
    cv::adaptiveThreshold(Igray, Iat, 255, adaptive_method, threshold_type, block_size, offset);

    cv::imshow("Raw", Igray);
    cv::imshow("Thesold", It);
    cv::imshow("Adaptive Threshold", Iat);
    cv::waitKey(0);
    return 0;

}