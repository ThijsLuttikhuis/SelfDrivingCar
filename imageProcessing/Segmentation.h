//
// Created by thijs on 17-10-19.
//

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include "../dataStructures/ColumnSegment.h"

#ifndef SELFDRIVINGCAR_SEGMENTATION_H
#define SELFDRIVINGCAR_SEGMENTATION_H

class Segmentation {
private:
    cv::Mat &image;

    bool showSegmentation;

    int minimumDelta;
    int thresholdColDistance;

    void* segmentationThread(void* arg);

    void thresholdColumn(ColumnSegment* columnSegment);

    bool thresholdPixel(const cv::Vec3b &pixel);

public:
    std::vector<ColumnSegment> segmentationRow;

    explicit Segmentation(cv::Mat &_image, bool showSegmentation, int thresholdMinimumDelta, int thresholdColDistance);

    void segmentImage(int nThreads, int startRow, int endRow);
    void segmentImage(int nThreads);

};



#endif //SELFDRIVINGCAR_SEGMENTATION_H
