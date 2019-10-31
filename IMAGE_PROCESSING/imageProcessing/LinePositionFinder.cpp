//
// Created by thijs on 23-10-19.
//

#include <iostream>
#include "LinePositionFinder.h"
#include "../utilities/Drawer.h"
#include "RoadLine.h"

std::vector<RoadLine> LinePositionFinder::findLinePositions(std::vector<Line>* lines) {
    if (!lines) return {};
    std::vector<RoadLine> roadLines;
    double minDistanceForSeperateLines = 150.0;
    double col;
    for (auto &line : *lines) {
        col = line.getColAtRow(image.rows-1);

        bool isSeperateLine = true;
        for (auto &roadLine : roadLines) {
            auto &existingCol = roadLine.lineColAtCar;
            if (fabs(col - existingCol) < minDistanceForSeperateLines) {
                isSeperateLine = false;
                roadLine.correspondingLines.push_back(line);

                double total = 0;
                for (auto &rl : roadLine.correspondingLines) {
                    total += rl.getColAtRow(image.rows-1);
                }
                existingCol = total / roadLine.correspondingLines.size();
                break;
            }

        }

        if (isSeperateLine) {
            RoadLine roadLine;
            roadLine.lineColAtCar = col;
            roadLine.correspondingLines = {line};
            roadLines.push_back(roadLine);

        }
    }
    return roadLines;
}
