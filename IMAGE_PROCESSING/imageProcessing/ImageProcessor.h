//
// Created by thijs on 17-10-19.
//

#ifndef SELFDRIVINGCAR_IMAGEPROCESSOR_H
#define SELFDRIVINGCAR_IMAGEPROCESSOR_H

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

#include "../dataStructures/ColumnSegment.h"
#include "Segmentation.h"
#include "../dataStructures/Line.h"
#include "LineFinder.h"
#include "../dataStructures/RoadLine.h"
#include "CarPositionFinder.h"


class ImageProcessor {
private:
    int nThreads;
    cv::Mat &image;

    // Filters
    Filters filters = {};

public:
    ImageProcessor(int nThreads, cv::Mat &image)
    : nThreads(nThreads), image(image) { }

    Segmentation segmentImage(CarPosition* &carPosition, bool showSegentation = false);

    std::vector<Line> findLines(Segmentation* segmentation, CarPosition* &carPosition, int showLines);

    void setFilters(Filters &filters);

    std::vector<RoadLine> getLinePositions(std::vector<Line>* lines, CarPosition* &carPosition);

    CarPosition* getCarPosition(std::vector<RoadLine>* roadLines, CarPosition* &carPosition, int showRoadLinePositions);
};

#endif //SELFDRIVINGCAR_IMAGEPROCESSOR_H
