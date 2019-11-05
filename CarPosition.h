//
// Created by thijs on 31-10-19.
//

#ifndef SELFDRIVINGCAR_CARPOSITION_H
#define SELFDRIVINGCAR_CARPOSITION_H

#include <iostream>

class CarPosition {
public:
    int d2LeftLine;
    int d2RightLine;
    int d2SecondLeftLine;
    int d2SecondRightLine;

    int lanesLeft;
    int lanesRight;

    double carAngleToRoad;

    double carAngle;
    double carSpeed;

    CarPosition(const CarPosition &copy) = default;

    explicit CarPosition() : d2LeftLine(-1), d2RightLine(-1),
                             lanesLeft(0), lanesRight(0),
                             d2SecondLeftLine(-1), d2SecondRightLine(-1),
                             carAngleToRoad(0), carAngle(0), carSpeed(0) {};

    void print() {
        std::cout << "distanceToRightLine: " << d2RightLine << std::endl <<
                  "distanceToLeftLine: " << d2LeftLine << std::endl <<
                  "distanceToSecondRightLine: " << d2SecondRightLine << std::endl <<
                  "distanceToSecondLeftLine: " << d2SecondLeftLine << std::endl <<
                  "lanesLeft: " << lanesLeft << std::endl <<
                  "lanesRight: " << lanesRight << std::endl <<
                  "carAngleToRoad: " << carAngleToRoad << std::endl <<
                  "carAngle: " << carAngle << std::endl <<
                  "carSpeed: " << carSpeed << std::endl;
    }

    bool operator ==(const CarPosition &other) const {
        return d2LeftLine == other.d2LeftLine &&
               d2RightLine == other.d2RightLine &&
                lanesLeft == other.lanesLeft &&
                lanesRight == other.lanesRight &&
               carAngleToRoad == other.carAngleToRoad &&
               carAngle == other.carAngle;
    }
};


#endif //SELFDRIVINGCAR_CARPOSITION_H
