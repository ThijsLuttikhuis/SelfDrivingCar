//
// Created by thijs on 01-11-19.
//

#include "gpio.h"
#ifdef USE_PI
#include <wiringPi.h>
#include <softPwm.h>
#include <iostream>
#include <zconf.h>
#endif

bool gpio::setup() {
#ifdef USE_PI
    std::cout << "Using WiringPi for GPIO" << std::endl;
    // Steer variables
    currentAngle = 12;
    rangeCamera = 400;
    rangeServo = 8;
    biasServo = 12;

    // Speed variables
    startSpeed = 40;
    startSpeed_t = 500;
    speed = 30;

    // Setup wiringPi
    wiringPiSetup();
    if (softPwmCreate(SERVO_PWM, 0, 100) || softPwmCreate(HBRUG_PWM, 0, 100)) {
        std::cout << "Error in creating softPwm" << std::endl;
        return false;
    }

    std::cout << "Starting Engine" << std::endl;
    softPwmWrite(HBRUG_PWM, startSpeed);
    sleep(1);
    softPwmWrite(HBRUG_PWM, speed);
#endif
    return true;
}

bool gpio::loop(CarPosition* carPosition) {
#ifdef USE_PI
    double &pid = carPosition->pid;

    double max_output = biasServo + (rangeServo/2);
    double min_output = biasServo - (rangeServo/2);
    double factor = rangeServo / rangeCamera;

    double output = factor*pid + biasServo;
    output = output > max_output ? max_output : output < min_output ? min_output : output;
    softPwmWrite(SERVO_PWM, static_cast<int>(output+0.5));
#endif
    return true;
}

void gpio::close() {
#ifdef USE_PI
    softPwmWrite(HBRUG_PWM, 0);
    sleep(1);
#endif
}
