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
    enum Direction {
        STRAIGHT,
        LEFT,
        RIGHT
    };
    enum Status {
        NONE,
        LINE,
        T_LEFT,
        T_RIGHT,
        EMERGENCY_STOP,
        RESET,
        STOP
    };

    double Kp;
    double Ki;
    double Kd;

    double error;
    double previousError;
    double errorSum;

    bool dataSet;

    CarPositionBuffer cPBuffer;

    CarPosition filter();

    void switchLane(Direction);

    Direction switchingTo;

    int marge;

    int status;
    int intermediate;
    int read;
    int readNew;

    int readFile();

    void clearFile();

    int writeFile(const char*, int, int);

    void writeControl(int input);


public:
    explicit control(cv::Mat &image) : node(image) {};

    bool setup() override;

    bool loop(CarPosition* carPosition) override;

    void close() override;

};

#endif //SELFDRIVINGCAR_CONTROL_H





