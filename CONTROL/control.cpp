
#include "control.h"
#include "FileReadWrite.h"
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
    //FileReadWrite::clearFile();
    read = 0;

    error = 0;
    cPBuffer = CarPositionBuffer();
    filterCP = false;

    return true;
}

bool control::loop(CarPosition* &carPosition) {
    if (!carPosition) return true;

    if (filterCP) {
        cPBuffer.push(*carPosition);
        *carPosition = filter();
    }

    previousState = state;
    state = FileReadWrite::readFile();
    // std::cout << "\"input.txt\" status: " << state << std::endl;

    switch (state) {
        case 1:
            return goStraight(carPosition);
        case 2:
            return goLeft(carPosition);
        case 3:
            return goRight(carPosition);
        case 4:
            return false;
        case 5:
            filterCP = !filterCP;
            std::cout << "setting filter to " << filterCP << "!" << std::endl;
            FileReadWrite::writeControl(previousState);
        case 6:
            carPosition->carAngle = 0;
            carPosition->carSpeed = 0;
            return true;
        default:
            std::cerr << "\nfile \"input.txt\" not set!!\n" << std::endl;
            carPosition->carAngle = 0;
            carPosition->carSpeed = 0;
            return true;
    }
}

void control::close() {

}

bool control::goStraight(CarPosition* &carPosition) {
    if (carPosition->lanesRight && carPosition->lanesLeft) {
        error = carPosition->d2LeftLine - carPosition->d2RightLine;
    }
    else {
        error = 0;
    }
    carPosition->carSpeed = 1;
    carPosition->carAngle = error;
    return true;
}

bool control::goLeft(CarPosition* &carPosition) {
    if (carPosition->d2SecondLeftLine < 0) {
        read = FileReadWrite::writeFile("Cannot turn left.", read, 2);
        FileReadWrite::writeControl(1);
        return goStraight(carPosition);
    }
    else {
        error = carPosition->d2SecondLeftLine - carPosition->d2RightLine;
    }
    carPosition->carSpeed = 1;
    carPosition->carAngle = error;
    return true;
}

bool control::goRight(CarPosition* &carPosition) {

    if (carPosition->d2SecondRightLine < 0) {
        read = FileReadWrite::writeFile("Cannot turn right.", read, 3);
        FileReadWrite::writeControl(1);
        return goStraight(carPosition);
    }
    else {
        error = carPosition->d2LeftLine - carPosition->d2SecondRightLine;
    }
    carPosition->carSpeed = 1;
    carPosition->carAngle = error;
    return true;
}
