//
// Created by thijs on 22-10-19.
//

#ifndef SELFDRIVINGCAR_FILTERS_H
#define SELFDRIVINGCAR_FILTERS_H

#include "RowCol.h"
#include "Line.h"
#include "RoadLine.h"

struct Filters {
public:
    RowCol horizon;
    int verticalLineMaxDistToHorizon;
    int minLineLength;
    int minDistToHorizon;
    int maxLineDistToHorizon;
    int minLineDistToOtherLine;
    int minRoadLinePoints;
    int minDistanceForSeperateLines;
    double maxLineGradientDifference;

    // thresholding image
    int thresholdMinimumDelta;
    int thresholdColDistance;

    // printing
    bool printCurrentHorizon;

    Filters() = default;

    bool preLineFilter(Line &line, const std::vector<Line> &otherLines);

    RowCol afterLineFilter(std::vector<Line>* lines);



    bool roadLineFilter(RoadLine &roadLine);

};

#endif //SELFDRIVINGCAR_FILTERS_H

