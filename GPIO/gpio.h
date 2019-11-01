//
// Created by thijs on 01-11-19.
//

#ifndef SELFDRIVINGCAR_GPIO_H
#define SELFDRIVINGCAR_GPIO_H

#include "../CarPosition.h"
#include "../node.h"

#define SERVO_PWM 4
#define HBRUG_PWM 0

class gpio : public node {
private:

// Steer variables
    double currentAngle = 12;
    double rangeCamera = 400;
    double rangeServo = 8;
    double biasServo = 12;

    // Speed variables
    double startSpeed = 40;
    double startSpeed_t = 500;
    double speed = 30;

// Inputs
    double pid = 100;

public:
    explicit gpio(cv::Mat &image) : node(image) {};

    bool setup() override;
    bool loop(CarPosition* carPosition) override;
    void close() override;
};



#endif //SELFDRIVINGCAR_GPIO_H
