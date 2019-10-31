//
// Created by thijs on 31-10-19.
//

#include "CarPositionFinder.h"

CarPosition CarPositionFinder::findCarPosition(std::vector<RoadLine>* roadLines) {
    CarPosition carPosition;

    int linesLeft = 0;
    int linesRight = 0;
    double closestLineColLeft = -filters.horizon.col;
    double closestLineColRight = filters.horizon.col*3;
    for (auto &roadLine : *roadLines) {
        if (showRoadLinePositions) {
            roadLine.drawSquareAtColumn(image);
        }

        double col = roadLine.lineColAtCar;
        if (col < filters.horizon.col) {
            linesLeft++;
            if (col > closestLineColLeft) {
                closestLineColLeft = col;
            }
        }
        else {
            linesRight++;
            if (col < closestLineColRight) {
                closestLineColRight = col;
            }
        }
    }
    if (linesLeft && linesRight) {
        carPosition.distanceToLeftLine = static_cast<int>(-closestLineColLeft + filters.horizon.col);
        carPosition.distanceToRightLine = static_cast<int>(closestLineColRight - filters.horizon.col);
        int &dLeft = carPosition.distanceToLeftLine;
        int &dRight = carPosition.distanceToRightLine;
        if (showRoadLinePositions) {
            if (dLeft < dRight) {
                Drawer::drawArrowRight(image, static_cast<double>(dRight * 1.0 / dLeft - 1.0));
            }
            else {
                Drawer::drawArrowLeft(image, static_cast<double>(dLeft * 1.0 / dRight - 1.0));
            }
        }
    }

}
