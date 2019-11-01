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
    int minDistanceForSeperateLines;

    // thresholding image
    int thresholdMinimumDelta;
    int thresholdColDistance;

    Filters() = default;

    bool preLineFilter(Line &line, const std::vector<Line> &otherLines, const std::vector<int>* dColDRow);

    void afterLineFilter(std::vector<Line>* lines);



    bool roadLineFilter(RoadLine &roadLine);
};

#endif //SELFDRIVINGCAR_FILTERS_H

