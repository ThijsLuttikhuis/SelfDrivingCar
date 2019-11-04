//
// Created by thijs on 31-10-19.
//

#ifndef SELFDRIVINGCAR_CARPOSITION_H
#define SELFDRIVINGCAR_CARPOSITION_H


class CarPosition {
public:
    int distanceToLeftLine;
    int distanceToRightLine;

    int lanesLeft;
    int lanesRight;

    double roadCurve;

    double pid;

    CarPosition() : distanceToLeftLine(0), distanceToRightLine(0),
                    lanesLeft(0), lanesRight(0), roadCurve(0), pid(0) {};

};


#endif //SELFDRIVINGCAR_CARPOSITION_H
