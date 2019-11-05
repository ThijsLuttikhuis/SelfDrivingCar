//
// Created by thijs on 31-10-19.
//

#ifndef SELFDRIVINGCAR_CONTROL_H
#define SELFDRIVINGCAR_CONTROL_H


#include "../CarPosition.h"
#include "../node.h"
#include "CarPositionBuffer.h"

class control : public node {
private:
    CarPositionBuffer cPBuffer;
    CarPosition filter();

    double error;

    int previousState;
    int state;
    int read;
    int readNew;
    bool filterCP;

public:
    explicit control(cv::Mat &image) : node(image) {};

    bool setup() override;

    bool loop(CarPosition* &carPosition) override;

    void close() override;

    bool goStraight(CarPosition* &carPosition);

    bool goLeft(CarPosition* &carPosition);

    bool goRight(CarPosition* &carPosition);

};

#endif //SELFDRIVINGCAR_CONTROL_H





