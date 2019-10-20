//
// Created by thijs on 17-10-19.
//

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

#include "dataStructures/ColumnSegment.h"
#include "dataStructures/Segmentation.h"
#include "dataStructures/Line.h"

#ifndef SELFDRIVINGCAR_IMAGEPROCESSOR_H
#define SELFDRIVINGCAR_IMAGEPROCESSOR_H

class ImageProcessor {
private:
    int nThreads;
    cv::Mat &image;
    int maxTimeOut = 8;

    // Horizon settings
    RowCol horizon;
    int minLineSegmentDistToHorizon = 20;
    int minRatioLineSegmentDistToHorizon = 2;
    int maxLineDistToHorizon = 60;

public:
    ImageProcessor(int nThreads, cv::Mat &image)
    : nThreads(nThreads), image(image), horizon(image.rows/2, image.cols/2){ }

    Segmentation segmentImage();

    std::vector<Line> findLines(Segmentation* segmentation, double minLineLength);

    RowCol recursiveSearch(Segmentation* segmentation, int row, int col, PIXEL previousEdge, int timeOut);

    void setHorizon(RowCol _horizon, int _minLineSegmentDistToHorizon = 20, int _minRatioLineSegmentDistToHorizon = 2, int _maxLineDistToHorizon = 50);
};

#endif //SELFDRIVINGCAR_IMAGEPROCESSOR_H
