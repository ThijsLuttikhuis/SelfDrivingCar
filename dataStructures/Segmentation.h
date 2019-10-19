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
    std::vector<ColumnSegment> segmentationRow;
    int xDist = 10;
    int minimumDelta = 10;

    void* segmentationThread(void* arg);

    void segmentColumn(ColumnSegment* columnSegment);

    void thresholdColumn(ColumnSegment* columnSegment);

    bool thresholdPixel(const cv::Vec3b &pixel);

public:
    explicit Segmentation(cv::Mat &_image);

    ColumnSegment getRow(int row) const;

    void setRow(const ColumnSegment& columnSegment);

    void segmentImage(int nThreads);

};

struct ThreadArgs {
    int startRow;
    int endRow;
};


#endif //SELFDRIVINGCAR_SEGMENTATION_H
