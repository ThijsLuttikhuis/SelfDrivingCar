
#include "control.h"
#include <fstream>

CarPosition control::filter() {

    CarPosition previous = cPBuffer.at(1);
    CarPosition current = cPBuffer.at(0);

    if (previous == CarPosition()) return current;
    if (current == CarPosition()) {
        current = previous;
        return current;
    }

    // If there is no current value, Take old value
    if (current.lanesLeft == 0 || current.lanesRight == 0) {
        current = previous;
        return current;
    }
    if (current.lanesLeft == 1 && previous.lanesLeft > 1) {
        current.lanesLeft = previous.lanesLeft;
        current.d2LeftLine = previous.d2LeftLine;
        current.d2SecondLeftLine = previous.d2SecondLeftLine;
    }
    if (current.lanesRight == 1 && previous.lanesRight > 1) {
        current.lanesRight = previous.lanesRight;
        current.d2RightLine = previous.d2RightLine;
        current.d2SecondRightLine = previous.d2SecondRightLine;
    }
    return current;
}

bool control::setup() {
    Kp = 1;
    Ki = 0;
    Kd = 0;

    error = 0;
    previousError = 0;
    errorSum = 0;
    switchingTo = STRAIGHT;

    clearFile();
    read = 0;
    marge = 0;

    cPBuffer = CarPositionBuffer();
    return true;
}

bool control::loop(CarPosition* &carPosition) {
    if (!carPosition) return true;
    if (carPosition->lanesRight && carPosition->lanesLeft) {
        error = carPosition->d2LeftLine - carPosition->d2RightLine;
    }
    else {
        error = 0;
    }

    carPosition->carSpeed = 1;
    carPosition->carAngle = error;
    return true;

    status = readFile();
    std::cout << "status: " << status << std::endl;
    switch (status) {
        case 1:
            switchLane(STRAIGHT);
            break;
        case 2:
            switchLane(LEFT);
            break;
        case 3:
            switchLane(RIGHT);
            break;
        case 4:
            return false;
        case 5:
            return false;
        case 6:
            carPosition->carAngle = 0;
            break;
        default:
            return true;
    }

    carPosition->carSpeed = 1;

    double sampleTime = 0.02;

    if (switchingTo == LEFT && carPosition->d2SecondLeftLine < 0) {
        read = writeFile("Cannot turn left.", read, 2);
        writeControl(1);
    }
    else {
        error = carPosition->d2SecondLeftLine - carPosition->d2RightLine;
    }

    if (switchingTo == RIGHT && carPosition->d2SecondRightLine < 0) {
        read = writeFile("Cannot turn right.", read, 3);
        writeControl(1);
    }
    else {
        error = carPosition->d2LeftLine - carPosition->d2SecondRightLine;
    }

    if (switchingTo != LEFT && switchingTo != RIGHT) {
        error = carPosition->d2LeftLine - carPosition->d2RightLine;
        switchingTo = STRAIGHT;
    }

    cPBuffer.push(*carPosition);
    *carPosition = filter();

    error = carPosition->d2LeftLine - carPosition->d2RightLine;
    errorSum += error;
    double pid = Kp * error + Ki * errorSum * sampleTime + Kd * (error - previousError) / sampleTime;
    previousError = error;

    carPosition->carAngle = pid;
    return true;
}

void control::close() {

}

void control::switchLane(Direction n) {
    switchingTo = n;
}

int control::readFile() {
    std::ifstream myfile("input.txt");
    if (myfile.is_open()) {
        while (myfile >> intermediate) {
            status = intermediate;
        }
        myfile.close();
    }
    return status;
}

void control::clearFile() {
    std::ofstream file("input.txt", std::ios::trunc);
}

int control::writeFile(const char* input, int read, int readNew) {
    if (read != readNew) {
        std::ofstream fout;
        fout.open("log.txt", std::ios::trunc);
        fout << input;
        fout.close();
    }
    read = readNew;
    return read;
}

void control::writeControl(int input) {
    std::ofstream fout;
    fout.open("input.txt", std::ios::trunc);
    fout << input;
    fout.close();
}