//
// Created by thijs on 22-10-19.
//

#ifndef SELFDRIVINGCAR_FILTERS_H
#define SELFDRIVINGCAR_FILTERS_H

#include "RowCol.h"
#include "Line.h"
#include "../imageProcessing/RoadLine.h"

struct Filters {
public:
    RowCol horizon;
    int minLineLength;
    int minDistToHorizon;
    int maxLineDistToHorizon;
    int minLineDistToOtherLine;
    int minRoadLinePoints;

    // thresholding image
    int thresholdMinimumDelta;
    int thresholdColDistance;

    Filters() = default;

    bool preFilter(RowCol startOfLine);

    bool lineFilter(Line &line, const std::vector<Line> &otherLines, const std::vector<int>* dColDRow);

    bool roadLineFilter(RoadLine &roadLine);
};

#endif //SELFDRIVINGCAR_FILTERS_H

