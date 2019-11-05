//
// Created by thijs on 31-10-19.
//

#include "CarPositionFinder.h"

CarPosition* CarPositionFinder::findCarPosition(std::vector<RoadLine>* roadLines) {
    auto* carPosition = new CarPosition();
    if (roadLines->size() < 2) return carPosition;

    double closestLineColLeft = -filters.horizon.col;
    double closestLineColRight = filters.horizon.col*3;
    double secondClosestLineColLeft = -filters.horizon.col;
    double secondClosestLineColRight = filters.horizon.col*3;
    for (auto &roadLine : *roadLines) {
        if (showRoadLinePositions) {
            roadLine.drawSquareAtColumn(image, 10);
        }
        double col = roadLine.lineColAtCar;
        if (col < filters.horizon.col) {
            carPosition->lanesLeft++;
            if (col > closestLineColLeft) {
                secondClosestLineColLeft = closestLineColLeft;
                closestLineColLeft = col;
            }
            else if (col > secondClosestLineColLeft) {
                secondClosestLineColLeft = col;
            }
        }
        else {
            carPosition->lanesRight++;
            if (col < closestLineColRight) {
                secondClosestLineColRight = closestLineColRight;
                closestLineColRight = col;
            }
            else if (col < secondClosestLineColRight) {
                secondClosestLineColRight = col;
            }
        }
    }
    if (carPosition->lanesLeft && carPosition->lanesRight) {
        carPosition->d2LeftLine = static_cast<int>(-closestLineColLeft + filters.horizon.col);
        carPosition->d2RightLine = static_cast<int>(closestLineColRight - filters.horizon.col);
        int &dLeft = carPosition->d2LeftLine;
        int &dRight = carPosition->d2RightLine;
        if (showRoadLinePositions) {
            if (dLeft < dRight) {
                Drawer::drawArrowRight(image, static_cast<double>(dRight * 1.0 / dLeft - 1.0));
            }
            else {
                Drawer::drawArrowLeft(image, static_cast<double>(dLeft * 1.0 / dRight - 1.0));
            }
        }
        if (carPosition->lanesLeft > 1) {
            carPosition->d2SecondLeftLine = static_cast<int>(-secondClosestLineColLeft + filters.horizon.col);
        }
        if (carPosition->lanesRight > 1) {
            carPosition->d2SecondRightLine = static_cast<int>(secondClosestLineColRight - filters.horizon.col);
        }
    }
    return carPosition;

}
