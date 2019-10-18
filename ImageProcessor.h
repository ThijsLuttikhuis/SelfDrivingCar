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
    int xDist = 10;
    int nThreads;
    int minimumDelta = 10;
    int maxGap;
    cv::Mat &image;

    void* segmentationThread(void* arg);
    void segmentColumn(ColumnSegment* columnSegment);
    void thresholdColumn(ColumnSegment* columnSegment);
    bool thresholdPixel(const cv::Vec3b &pixel);

public:
    ImageProcessor(int nThreads, int maxGap, cv::Mat &image)
    : nThreads(nThreads), maxGap(maxGap), image(image) {};

    Segmentation segmentImage();

    void groupColumnSegment(ColumnSegment* pVector);
};

struct ThreadArgs {
    Segmentation* segmentation;
    int startRow;
    int endRow;
};



#endif //SELFDRIVINGCAR_IMAGEPROCESSOR_H
