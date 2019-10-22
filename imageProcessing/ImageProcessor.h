//
// Created by thijs on 17-10-19.
//

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

#include "../dataStructures/ColumnSegment.h"
#include "Segmentation.h"
#include "../dataStructures/Line.h"

#ifndef SELFDRIVINGCAR_IMAGEPROCESSOR_H
#define SELFDRIVINGCAR_IMAGEPROCESSOR_H

class ImageProcessor {
private:
    int nThreads;
    cv::Mat &image;

    // Horizon settings
    RowCol horizon;
    int minDistToHorizon;
    int maxLineDistToHorizon;
    int minLineLength;

public:
    ImageProcessor(int nThreads, cv::Mat &image)
    : nThreads(nThreads), image(image) { }

    Segmentation segmentImage(bool showSegentation = false);

    std::vector<Line> findLines(Segmentation* segmentation, bool showLines);



    void setHorizon(RowCol _horizon, int _minLineSegmentDistToHorizon, int _maxLineDistToHorizon);

    void setMinLineLength(int _minLineLength);

    std::vector<RowCol> getLinePositions(std::vector<Line>* lines);
};

#endif //SELFDRIVINGCAR_IMAGEPROCESSOR_H
