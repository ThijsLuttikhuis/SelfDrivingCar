//
// Created by thijs on 28-10-19.
//

#include <iostream>
#include "Filters.h"
#include "Line.h"

enum DIR {
    RIGHT,
    STRAIGHT,
    LEFT
};

bool Filters::preFilter(RowCol startOfLine) {
    // filter lines too close to the horizon
//    if (startOfLine.dist2(horizon) < minDistToHorizon*minDistToHorizon) return false;

    return true;
}

bool Filters::lineFilter(Line &line, const std::vector<Line> &otherLines, const std::vector<int>* dColDRow) {

    // Filters after
    if (line.end.row == -1 || line.end.col == -1) return false;

    // Filter line length
    auto dcdrSize = static_cast<int>(dColDRow->size());
    if (dcdrSize < minLineLength) return false;
    if (line.length2() < minLineLength * minLineLength) return false;

    // Filter line too close to the horizon
    if (line.start.dist2(horizon) < minDistToHorizon*minDistToHorizon &&
        line.end.dist2(horizon) < minDistToHorizon*minDistToHorizon) return false;


    return true;

    // Fiter direction of the line (towards horizon point)
    double distanceToHorizon = line.horizontalDist2ToPoint(horizon); // left ==> dth < 0
    if (distanceToHorizon > maxLineDistToHorizon * maxLineDistToHorizon) {
        // Actually fine, if the line is long enough, but line is not straight, or the car is not straight.
        if (line.length2() < minLineLength*minLineLength*2*2) return false;
        line.isCurved = true;
        return false;
    }

    // Filter if another line is already very close
    bool isCloseToOtherLine = false;
    for (auto &otherLine : otherLines) {
        if (otherLine.start.dist2(line.start) < minLineDistToOtherLine * minLineDistToOtherLine &&
            otherLine.end.dist2(line.end) < minLineDistToOtherLine * minLineDistToOtherLine) {
            isCloseToOtherLine = true;
            break;
        }
    }
    if (isCloseToOtherLine) return false;

    return true;
}