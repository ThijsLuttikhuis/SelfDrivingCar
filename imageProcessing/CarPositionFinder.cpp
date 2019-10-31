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
        roadLine.drawSquareAtColumn(image);

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
        double distanceLeft = -closestLineColLeft + filters.horizon.col;
        double distanceRight = closestLineColRight - filters.horizon.col;

        if (distanceLeft < distanceRight) {
            Drawer::drawArrowRight(image);
        }
        else {
            Drawer::drawArrowLeft(image);
        }
    }

}
