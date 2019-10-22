//
// Created by thijs on 17-10-19.
//

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

#include "../dataStructures/ColumnSegment.h"
#include "Segmentation.h"
#include "../dataStructures/Line.h"
#include "LineFinder.h"

#ifndef SELFDRIVINGCAR_IMAGEPROCESSOR_H
#define SELFDRIVINGCAR_IMAGEPROCESSOR_H

class ImageProcessor {
private:
    int nThreads;
    cv::Mat &image;

    // Filters
    Filters filters = {};

public:
    ImageProcessor(int nThreads, cv::Mat &image)
    : nThreads(nThreads), image(image) { }

    Segmentation segmentImage(bool showSegentation = false);

    std::vector<Line> findLines(Segmentation* segmentation, bool showLines);



    void setHorizon(RowCol horizon, int minLineSegmentDistToHorizon, int maxLineDistToHorizon);

    void setMinLineLength(int minLineLength);

    std::vector<RowCol> getLinePositions(std::vector<Line>* lines);
};

#endif //SELFDRIVINGCAR_IMAGEPROCESSOR_H
