//
// Created by thijs on 28-10-19.
//

#include <iostream>
#include "Filters.h"
#include "Line.h"

bool Filters::preLineFilter(Line &line, const std::vector<Line> &otherLines) {

    // Filters after
    if (line.end.row == -1 || line.end.col == -1) return false;
    // Filter line length
    auto dcdrSize = static_cast<int>(line.dRowDCol.size());
    if (dcdrSize < minLineLength) return false;
    if (line.length2() < minLineLength * minLineLength) return false;

    // Filter line too close to the horizon
    if (line.start.dist2(horizon) < minDistToHorizon*minDistToHorizon &&
        line.end.dist2(horizon) < minDistToHorizon*minDistToHorizon) return false;

    // Filter if another line is already very close
    for (auto &otherLine : otherLines) {
        if (otherLine.start.dist2(line.start) < minLineDistToOtherLine * minLineDistToOtherLine &&
            otherLine.end.dist2(line.end) < minLineDistToOtherLine * minLineDistToOtherLine) {
            return false;
        }
    }

    return true;
}

RowCol Filters::afterLineFilter(std::vector<Line>* lines) {
    if (lines->size() <= 2) return horizon;

    // Get weighted average Column at the horizon
    double sumCols = 0;
    int totalLines = 0;
    for (auto &line : *lines)  {
        totalLines += line.verticalLength();
        sumCols += line.verticalLength() * line.getColAtRow(horizon.row);
    }
    RowCol newHorizonRC = RowCol(horizon.row, static_cast<int>(sumCols / totalLines));

    if (printCurrentHorizon) {
    std::cout << "current horizon is at: " << newHorizonRC.row << " x " << newHorizonRC.col << std::endl;
    }

    int &maxldth = maxLineDistToHorizon;
    lines->erase(std::remove_if(lines->begin(), lines->end(), [maxldth, newHorizonRC] (Line &line) {
        return line.dist2ToPoint(newHorizonRC.row, newHorizonRC.col) > maxldth*maxldth ;
    }),lines->end());

    return newHorizonRC;
}

bool Filters::roadLineFilter(RoadLine &roadLine) {
    int sum = 0;
    int longestPart = 0;
    double a = 0.0;
    for (auto &line : roadLine.correspondingLines) {
        int size = line.dRowDCol.size();
        sum += size;

        if (size > longestPart) {
            longestPart = size;
            a = line.a;
        }
    }
    if (sum < minRoadLinePoints) return false;

    for (auto &line : roadLine.correspondingLines) {
        if (line.a / a < maxLineGradientDifference || a / line.a < maxLineGradientDifference) {
            return false;
        }
    }

    return true;
}
