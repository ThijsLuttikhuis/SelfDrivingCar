
#include "control.h"

bool control::setup() {
    Kp = 0.0001;
    Ki = 0;
    Kd = 0;

    error = 0;
    previousError = 0;
    errorSum = 0;

    return true;
}

bool control::loop(CarPosition* carPosition) {
    double sampleTime = 0;

    previousError = error;
    error = carPosition->distanceToLeftLine - carPosition->distanceToRightLine;
    errorSum += error;
    double pid = Kp * error + Ki *errorSum *sampleTime + Kd * (error-previousError)/sampleTime;

    carPosition->pid = pid;
    return true;
}

void control::close() {

}


