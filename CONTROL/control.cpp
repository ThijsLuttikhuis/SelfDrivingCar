
#include "control.h"

bool control::setup() {
    Kp = 1;
    Ki = 0;
    Kd = 0;

    error = 0;
    previousError = 0;
    errorSum = 0;

    dataSet = false;

    return true;
}

void control::filter(CarPosition* carPosition) {
    if (!dataSet) return;
}

bool control::loop(CarPosition* carPosition) {
    filter(carPosition);

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



