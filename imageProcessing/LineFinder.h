//
// Created by thijs on 22-10-19.
//

#ifndef SELFDRIVINGCAR_LINEFINDER_H
#define SELFDRIVINGCAR_LINEFINDER_H

#include "../dataStructures/RowCol.h"
#include <vector>
#include "../dataStructures/Line.h"
#include "Segmentation.h"


struct Filters {
public:
    RowCol horizon;
    int minLineLength;
    int minDistToHorizon;
    int maxLineDistToHorizon;
    Filters(RowCol horizon, int minLineLength, int minDistToHorizon, int maxLineDistToHorizon) :
          horizon(horizon), minLineLength(minLineLength), minDistToHorizon(minDistToHorizon), maxLineDistToHorizon(maxLineDistToHorizon) {};
};

class LineFinder {
private:
    cv::Mat &image;

    int maxTimeOut = 8;
    int minLineLength;
    RowCol horizon;
    int minDistToHorizon;
    int maxLineDistToHorizon;
    bool showLines;

    RowCol recursiveSearch(Segmentation* segmentation, int row, int col, PIXEL previousEdge);

    bool preFilter(const RowCol &startOfLine);

    bool lineFilter(const Line &line, const std::vector<Line> &otherLines);
public:
    LineFinder(cv::Mat &image, Filters filters, bool showLines) :
    image(image), minLineLength(filters.minLineLength), horizon(filters.horizon),
    minDistToHorizon(filters.minDistToHorizon), maxLineDistToHorizon(filters.maxLineDistToHorizon), showLines(showLines) {};

    std::vector<Line> findLines(Segmentation* segmentation);

};

#endif //SELFDRIVINGCAR_LINEFINDER_H
