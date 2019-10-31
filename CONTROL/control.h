//
// Created by thijs on 31-10-19.
//

#ifndef SELFDRIVINGCAR_CONTROL_H
#define SELFDRIVINGCAR_CONTROL_H


#include "../CarPosition.h"
#include "../stack.h"

class control : public stack {
private:
    double Kp;
    double Ki;
    double Kd;

    double error;
    double previousError;
    double errorSum;

public:
    explicit control(cv::Mat &image) : stack(image) {};
    bool setup() override;
    bool loop(CarPosition* carPosition) override;
    void close() override;
};

#endif //SELFDRIVINGCAR_CONTROL_H
