//
// Created by thijs on 17-10-19.
//

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include "dataStructures/RowCol.h"

#ifndef SELFDRIVINGCAR_DRAWER_H
#define SELFDRIVINGCAR_DRAWER_H

class Drawer {
private:
    static bool initShowImage;
    static bool debug;

    static cv::VideoCapture capture;

public:
    static bool showImage(cv::Mat &image, bool frameByFrame);

    static bool getNextFrame(cv::Mat &image);

    static void closeVideo();

    static bool startVideo(cv::String &filename);

    static void setPixel(cv::Vec3b &pixel, const cv::Vec3b &color);

    static void setPixel(cv::Mat &image, int row, int col, const cv::Vec3b &color);

    static void setPixel(cv::Mat &image, RowCol rowCol, const cv::Vec3b &color);

    static void setDebug();
};


#endif //SELFDRIVINGCAR_DRAWER_H
