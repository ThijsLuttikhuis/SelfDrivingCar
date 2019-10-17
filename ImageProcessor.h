//
// Created by thijs on 17-10-19.
//

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

#include "dataStructures/ColumnSegment.h"
#include "dataStructures/Segmentation.h"

#ifndef SELFDRIVINGCAR_IMAGEPROCESSOR_H
#define SELFDRIVINGCAR_IMAGEPROCESSOR_H


class ImageProcessor {
private:
    int nThreads;
    int skip;
    cv::Mat* image;
    cv::VideoCapture capture;
    bool initShowImage = false;

    static void* segmentationThread(void* arg);

public:
    ImageProcessor(int nThreads, int skip, cv::Mat* image) : nThreads(nThreads), skip(skip), image(image) {};

    Segmentation segmentImage();

    bool startVideo(cv::String &filename);
    bool getNextFrame();
    bool showImage();
    void closeVideo();
};

struct ThreadArgs {
    Segmentation* segmentation;
    int startRow;
    int endRow;
    int skip;
};



#endif //SELFDRIVINGCAR_IMAGEPROCESSOR_H
