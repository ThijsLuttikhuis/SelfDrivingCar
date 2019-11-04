
#include "control.h"

CarPosition control::filter() {

    CarPosition previous = cPBuffer.at(1);
    CarPosition current = cPBuffer.at(0);
    return current;
}

bool control::setup() {
    Kp = 1;
    Ki = 0;
    Kd = 0;

    error = 0;
    previousError = 0;
    errorSum = 0;

    cPBuffer = CarPositionBuffer();
    return true;
}


bool control::loop(CarPosition* carPosition) {
    if (!carPosition) return true;

    cPBuffer.push(*carPosition);
    filter();

    double sampleTime = 0.05;

    previousError = error;
    error = carPosition->distanceToLeftLine - carPosition->distanceToRightLine;
    errorSum += error;
    double pid = Kp * error + Ki *errorSum *sampleTime + Kd * (error-previousError)/sampleTime;

    carPosition->pid = pid;
    return true;
}

void control::close() {

}



