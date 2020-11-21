#include "learnopencv.h"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/opencv.hpp"

#include <iostream>
#include <fstream>
#include <string>

int writeavi(int argc, char *argv[]) {
    cv::namedWindow("Example", cv::WINDOW_AUTOSIZE);
    cv::namedWindow("Log_Polar", cv::WINDOW_AUTOSIZE);

    cv::VideoCapture capture(argv[1]);
    double fps = capture.get(cv::CAP_PROP_FPS);
    cv::Size size(
        (int)capture.get(cv::CAP_PROP_FRAME_WIDTH),
        (int)capture.get(cv::CAP_PROP_FRAME_HEIGHT)
    );

    cv::VideoWriter writer;
    writer.open(argv[2], CV_FOURCC('M', 'J', 'P', 'G'), fps, size);
    cv::Mat logpolar_frame, bgr_frame;
    for (;;) {
        capture >> bgr_frame;
        if (bgr_frame.empty()) {
            break;
        }
        cv::imshow("Example", bgr_frame);
        cv::logPolar(
            bgr_frame,
            logpolar_frame,
            cv::Point2f(
                (float)bgr_frame.cols / 2,
                (float)bgr_frame.rows / 2
            ),
            40,
            cv::WARP_FILL_OUTLIERS
        );
        cv::imshow("Log_Polar", logpolar_frame);
        writer << logpolar_frame;
        char c = cv::waitKey(10);
        if (c == 27) {
            break;
        }
    }
    cv::destroyWindow("Example");
    cv::destroyWindow("Log_Polar");
    return 0;
}

int openmedia(int argc, char *argv[]) {
    cv::namedWindow("Example2", cv::WINDOW_AUTOSIZE);
    cv::VideoCapture cap;
    if (1 == argc) {
        cap.open(0);
    }
    else {
        cap.open(argv[1]);
    }
    
    cv::Mat frame;
    for (;;) {
        cap >> frame;
        if (frame.empty()) {
            break;
        }
        cv::imshow("Example2", frame);
        if (cv::waitKey(33) >= 0) {
            break;
        }
    }
    return 0;
}

#if 0
int testcode() {
    int x = 16, y = 32;
    cv::Vec3b intensity = img_rgb.at<cv::Vec3b>(y, x);
    uchar blue = intensity[0];
    uchar green = intensity[1];
    uchar red = intensity[2];

    std::cout << "At (x, y) = (" << x << ", " << y <<
        "): (blue, green, red) = (" <<
        (unsigned int)blue << ", "
        (unsigned int)green << ", "
        (unsigned int)red << 
        << ")" << std::endl;
    std::cout << "Gray pixel there is: " <<
        (unsigned int)img_gray.at<uchar>(y, x) << std::endl;
    x /= 4;
    y /= 4;
    std::cout << "Pyramid2 pixel there is: " <<
        (unsigned int)img_pyr2.at<uchar>(y, x) << std::endl;
    img_canny.at<uchar>(x, y) = 128;
}
#endif

int imagecanny(int argc, char *argv[])
{
    cv::Mat img_rgb, img_gray, img_canny;
    cv::namedWindow("Example6_RGB", cv::WINDOW_AUTOSIZE);
    cv::namedWindow("Example6_GRAY", cv::WINDOW_AUTOSIZE);
    cv::namedWindow("Example6_CANNY", cv::WINDOW_AUTOSIZE);

    img_rgb = cv::imread(argv[1]);
    cv::imshow("Example6_RGB", img_rgb);

    cv::cvtColor(img_rgb, img_gray, cv::COLOR_BGR2GRAY);
    cv::imshow("Example6_GRAY", img_gray);

    cv::Canny(img_gray, img_canny, 10, 100, 3, true);
    cv::imshow("Example6_CANNY", img_canny);

    cv::waitKey(0);
    return 0;
}

int imagedown(int argc, char *argv[]) {
    cv::Mat img_in, img_out;
    cv::namedWindow("Example5_in", cv::WINDOW_AUTOSIZE);
    cv::namedWindow("Example5_out", cv::WINDOW_AUTOSIZE);

    img_in = cv::imread(argv[1]);
    cv::imshow("Example5_in", img_in);

    cv::pyrDown(img_in, img_out);
    cv::imshow("Example5_out", img_out);
    cv::waitKey(0);
    return 0;
}

static void imgproc(const cv::Mat &image) {
    /*create some windows to show the input and output images in*/
    cv::namedWindow("Example4_in", cv::WINDOW_AUTOSIZE);
    cv::namedWindow("Example4_out", cv::WINDOW_AUTOSIZE);

    /*create a window to show our input image*/
    cv::imshow("Example4_in", image);

    /*create an image to hold the smoothed output*/
    cv::Mat out;

    /*Do the smoothing(Note: Could use GaussianBlur(), blur(), medianBlur() or bilateralFilter().)*/
    cv::GaussianBlur(image, out, cv::Size(5, 5), 3, 3);
    cv::GaussianBlur(out, out, cv::Size(5, 5), 3, 3);

    /*Show the smoothed image in the output window*/
    cv::imshow("Example4_out", out);

    cv::waitKey(0);
}

int imageblur(int argc, char *argv[]) {
    cv::Mat image = cv::imread(argv[1]);
    imgproc(image);
    return 0;
}

static int g_slider_position = 0;
static int g_run = 1;
static int g_dontset = 0;  /*start out in single step mode*/
cv::VideoCapture g_cap;

void onTrackbarSlide(int pos, void *) {
    g_cap.set(cv::CAP_PROP_POS_FRAMES, pos);
    if (!g_dontset) {
        g_run = 1;
    }
    g_dontset = 0;
}

int ctrlvideo(int argc, char *argv[]) {
    cv::namedWindow("Example3", cv::WINDOW_AUTOSIZE);
    g_cap.open(std::string(argv[1]));
    int frames = (int)g_cap.get(cv::CAP_PROP_FRAME_COUNT);
    int tempw = (int)g_cap.get(cv::CAP_PROP_FRAME_WIDTH);
    int temph = (int)g_cap.get(cv::CAP_PROP_FRAME_HEIGHT);
    std::cout << "Video has " << frames << " frames of dimensions(" << tempw << "," << temph << ")." << std::endl;

    cv::createTrackbar("Position", "Example3", &g_slider_position, frames, onTrackbarSlide);
    cv::Mat frame;
    for (;;) {
        if (g_run != 0) {
            g_cap >> frame;
            if (frame.empty()) {
                break;
            }
            int current_pos = (int)g_cap.get(cv::CAP_PROP_POS_FRAMES);
            g_dontset = 1;
            cv::setTrackbarPos("Position", "Example3", current_pos);
            cv::imshow("Example3", frame);
            g_run -= 1;
        }
        char c = (char)cv::waitKey(33);
        if (c == 's') {
            g_run = 1;
            std::cout << "Single step, run = " << g_run << std::endl;
        } 
        if (c == 'r') {
            g_run = -1;
            std::cout << "Run mode, run = " << g_run << std::endl;
        }
        if (c == 27) {
            break;
        }
    }
    cv::destroyWindow("Example3");
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
        cv::imshow("Example2", frame);
        if (cv::waitKey(33) >= 0) {
            break;
        }
    }
    return 0;
}

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

