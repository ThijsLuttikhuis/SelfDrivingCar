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
    int skipRow;
    int skipCol;
    int minimumDelta;
    cv::Mat &image;

    void* segmentationThread(void* arg);
    std::vector<int> segmentColumn(int row);
    void thresholdColumn(int row, std::vector<int>* columnSegment);
    bool thresholdPixel(const cv::Vec3b &pixel);

public:
    ImageProcessor(int nThreads, int skipRow, int skipCol, int minimumDelta, cv::Mat &image)
    : nThreads(nThreads), skipRow(skipRow), skipCol(skipCol), minimumDelta(minimumDelta), image(image) {};

    Segmentation segmentImage();
};

struct ThreadArgs {
    Segmentation* segmentation;
    int startRow;
    int endRow;
};



#endif //SELFDRIVINGCAR_IMAGEPROCESSOR_H
