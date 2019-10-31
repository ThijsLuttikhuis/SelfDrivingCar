//
// Created by thijs on 31-10-19.
//

#ifndef SELFDRIVINGCAR_CARPOSITION_H
#define SELFDRIVINGCAR_CARPOSITION_H


class CarPosition {
public:
    int distanceToLeftLine;
    int distanceToRightLine;

    bool laneLeftExists;
    bool laneRightExists;

    double roadCurve;

    CarPosition() : distanceToLeftLine(0), distanceToRightLine(0),
                    laneLeftExists(false), laneRightExists(false), roadCurve(0) {};

};


#endif //SELFDRIVINGCAR_CARPOSITION_H
