//
// Created by thijs on 17-10-19.
//

#include "Drawer.h"
#include <iostream>
#include "../dataStructures/RowCol.h"

bool Drawer::initShowOriginalImage = false;
bool Drawer::initShowSegmentedImage = false;

int Drawer::debug = false;
int Drawer::showOriginalImage = false;

cv::Mat Drawer::copy;
cv::VideoCapture Drawer::capture = {};

void Drawer::setPixel(char &pixel, const uchar &color) {
    if (!debug) return;

    pixel = color;

}

void Drawer::setPixel(int row, int col, const uchar &color) {
    if (!debug) return;

    auto &pixel = copy.at<char>(row, col);
    setPixel(pixel, color);
}

void Drawer::setPixel(RowCol rowCol, const uchar &color) {
    if (!debug) return;

    setPixel(rowCol.row, rowCol.col, color);
}

bool Drawer::showImage(cv::Mat &image, bool frameByFrame) {
    if (!debug) return true;
    if (!showOriginalImage) return showImage(frameByFrame);
    if (showOriginalImage > 1) showImage(frameByFrame);

    if (!initShowOriginalImage) {
        initShowOriginalImage=true;
        cv::namedWindow("Original Image window", cv::WINDOW_NORMAL); // Create a window for display.
        cv::resizeWindow("Original Image window", 640, 480);
        cv::moveWindow("Original Image window", 700, 60);
    }

    cv::imshow("Original Image window", image);
    return cv::waitKey((int) !frameByFrame) != 27;
}

bool Drawer::showImage(bool frameByFrame) {
    if (!debug) return true;

    if (!initShowSegmentedImage) {
        initShowSegmentedImage=true;
        cv::namedWindow("Segmented Image window", cv::WINDOW_NORMAL); // Create a window for display.
        cv::resizeWindow("Segmented Image window", 640, 480);
        cv::moveWindow("Segmented Image window", 60, 60);
    }
    cv::imshow("Segmented Image window", copy);
    return cv::waitKey((int) !frameByFrame || showOriginalImage) != 27;
}

bool Drawer::startVideo(cv::String &filename) {
    cv::VideoCapture _capture = cv::VideoCapture(0);
    if (filename != "WEBCAM") {
        _capture = cv::VideoCapture(filename);
    }
    capture = _capture;
    if (!capture.isOpened()) {
        std::cerr << "Error opening video stream or file" << std::endl;
        return false;
    }

    return true;
}

void Drawer::closeVideo() {
    capture.release();
    cv::destroyAllWindows();
}

bool Drawer::getNextFrame(cv::Mat &image) {
    capture >> image;
    return !image.empty();
}

void Drawer::clearCopy(cv::Mat &image) {
    if (!debug) return;

    copy = cv::Mat::zeros(image.rows, image.cols, CV_8UC1);

   // image.copyTo(copy);
}

void Drawer::setDebug(int _debug) {
    debug = _debug;
}

void Drawer::setShowOriginalImage(int _showOriginalImage) {
    showOriginalImage = _showOriginalImage;
}
