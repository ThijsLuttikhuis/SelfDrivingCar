//
// Created by thijs on 17-10-19.
//

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include "../dataStructures/RowCol.h"

#ifndef SELFDRIVINGCAR_DRAWER_H
#define SELFDRIVINGCAR_DRAWER_H

class Drawer {
private:
    static bool initShowOriginalImage;
    static bool initShowSegmentedImage;

    static int debug;
    static int showOriginalImage;

    static cv::Mat copy;
    static cv::VideoCapture capture;

    static void setPixel(char &pixel, const uchar &color);
    static bool showImage(bool frameByFrame);

public:
    static bool showImage(cv::Mat &image, bool frameByFrame);

    static bool getNextFrame(cv::Mat &image);

    static void closeVideo();

    static bool startVideo(cv::String &filename);

    static bool startWebcam();

    static void setPixel(int row, int col, const uchar &color);

    static void setPixel(RowCol rowCol, const uchar &color);

    static void clearCopy(cv::Mat &mat);

    static void setDebug(int debug);

    static void setShowOriginalImage(int showOriginaImage);

    static void drawArrowLeft(cv::Mat &image, double factor = 1);

    static void drawArrowRight(cv::Mat &image, double factor = 1);

    static void drawArrow(RowCol start, RowCol end, int thickness);
};


#endif //SELFDRIVINGCAR_DRAWER_H
