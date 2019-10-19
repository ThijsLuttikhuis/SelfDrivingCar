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
    cv::Mat &image;

public:
    ImageProcessor(int nThreads, cv::Mat &image)
    : nThreads(nThreads), image(image) {};

    Segmentation segmentImage();
};

#endif //SELFDRIVINGCAR_IMAGEPROCESSOR_H
