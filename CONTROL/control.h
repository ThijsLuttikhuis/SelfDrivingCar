//
// Created by thijs on 31-10-19.
//

#ifndef SELFDRIVINGCAR_CONTROL_H
#define SELFDRIVINGCAR_CONTROL_H


#include "../CarPosition.h"
#include "../node.h"

class control : public node {
private:
    double Kp;
    double Ki;
    double Kd;

    double error;
    double previousError;
    double errorSum;

    bool dataSet;

    void filter(CarPosition* carPosition);

public:
    explicit control(cv::Mat &image) : node(image) {};
    bool setup() override;
    bool loop(CarPosition* carPosition) override;
    void close() override;

};

#endif //SELFDRIVINGCAR_CONTROL_H
