//
// Created by thijs on 17-10-19.
//

#include "Drawer.h"
#include <iostream>
#include "dataStructures/RowCol.h"

bool Drawer::initShowImage = false;
bool Drawer::debug = false;
cv::VideoCapture Drawer::capture = {};

void Drawer::setPixel(cv::Vec3b &pixel, const cv::Vec3b &color) {
    if (!debug) return;

    pixel[0] = color[0];
    pixel[1] = color[1];
    pixel[2] = color[2];
}

void Drawer::setPixel(cv::Mat &image, int row, int col, const cv::Vec3b &color) {
    if (!debug) return;

    auto &pixel = image.at<cv::Vec3b>(row, col);
    setPixel(pixel, color);
}

void Drawer::setPixel(cv::Mat &image, RowCol rowCol, const cv::Vec3b &color) {
    if (!debug) return;

    setPixel(image, rowCol.row, rowCol.col, color);
}

bool Drawer::showImage(cv::Mat &image) {
    if (!debug) return true;

    if (!initShowImage) {
        initShowImage=true;
        cv::namedWindow("Display window", cv::WINDOW_NORMAL); // Create a window for display.
        cv::resizeWindow("Display window", 1366, 768);
    }
    cv::imshow("Display window", image);
    return cv::waitKey(1) != 27;
}

bool Drawer::startVideo(cv::String &filename) {
    cv::VideoCapture _capture(filename);
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

void Drawer::setDebug() {
    debug = true;
}
