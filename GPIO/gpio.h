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
    double currentAngle;
    double rangeCamera;
    double rangeServo;
    double biasServo;

    // Speed variables
    double startSpeed;
    double startSpeed_t;
    double speed;

public:
    explicit gpio(cv::Mat &image) : node(image) {};

    bool setup() override;
    bool loop(CarPosition* carPosition) override;
    void close() override;
};



#endif //SELFDRIVINGCAR_GPIO_H
