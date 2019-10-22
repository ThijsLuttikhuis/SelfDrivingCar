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

    Filters() : Filters({}, 0, 0, 0) {};
    Filters(RowCol horizon, int minLineLength, int minDistToHorizon, int maxLineDistToHorizon) :
          horizon(horizon), minLineLength(minLineLength), minDistToHorizon(minDistToHorizon), maxLineDistToHorizon(maxLineDistToHorizon) {};
};

class LineFinder {
private:
    cv::Mat &image;

    Filters filters;

    int maxTimeOut = 8;
    bool showLines;

    RowCol recursiveSearch(Segmentation* segmentation, int row, int col, PIXEL previousEdge);

    bool preFilter(const RowCol &startOfLine);

    bool lineFilter(const Line &line, const std::vector<Line> &otherLines);
public:
    LineFinder(cv::Mat &image, Filters filters, bool showLines) :
    image(image), filters(filters), showLines(showLines) {};

    std::vector<Line> findLines(Segmentation* segmentation);

};

#endif //SELFDRIVINGCAR_LINEFINDER_H
