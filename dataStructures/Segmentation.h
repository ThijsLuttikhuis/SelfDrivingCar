//
// Created by thijs on 17-10-19.
//

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include "ColumnSegment.h"

#ifndef SELFDRIVINGCAR_SEGMENTATION_H
#define SELFDRIVINGCAR_SEGMENTATION_H

class Segmentation {
private:
    cv::Mat &image;

    int xDist = 18;
    int minimumDelta = 20;

    void* segmentationThread(void* arg);

    void thresholdColumn(ColumnSegment* columnSegment);

    bool thresholdPixel(const cv::Vec3b &pixel);

public:
    std::vector<ColumnSegment> segmentationRow;

    explicit Segmentation(cv::Mat &_image);

    void segmentImage(int nThreads, int startRow, int endRow);
    void segmentImage(int nThreads);

};

struct ThreadArgs {
    int startRow;
    int endRow;
};


#endif //SELFDRIVINGCAR_SEGMENTATION_H
