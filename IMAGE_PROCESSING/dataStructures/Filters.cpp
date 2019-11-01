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


bool Filters::preLineFilter(Line &line, const std::vector<Line> &otherLines, const std::vector<int>* dColDRow) {

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
}


void Filters::afterLineFilter(std::vector<Line>* lines) {
    // Filter if another line is already very close
//    for (auto &otherLine : otherLines) {
//        if (otherLine.start.dist2(line.start) < minLineDistToOtherLine * minLineDistToOtherLine &&
//            otherLine.end.dist2(line.end) < minLineDistToOtherLine * minLineDistToOtherLine) {
//            std::cout << "too close to other line . exe tm xd haha 1234567890       string" << std::endl;
//            return false;
//        }
//    }

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
        if (line.a / a < 0.7 || a / line.a < 0.7) {
            return false;
        }
    }

    return true;
}
