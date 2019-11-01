//
// Created by thijs on 01-11-19.
//

#include <zconf.h>
#include "gpio.h"

#ifdef USE_PI
#include <wiringPi.h>
#include <softPwm.h>
#endif

bool gpio::setup() {
#ifdef USE_PI
    std::cout << "Using WiringPi for GPIO" << std::endl;
    wiringPiSetup();
    if (softPwmCreate(SERVO_PWM, 0, 100) || softPwmCreate(HBRUG_PWM, 0, 100)) ;

    softPwmWrite(HBRUG_PWM, startSpeed);
    sleep(1);
    softPwmWrite(HBRUG_PWM, speed);
#endif
    return true;
}

bool gpio::loop(CarPosition* carPosition) {
#ifdef USE_PI
    pid = carPosition->pid;

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
#endif
}
