//
// Created by thijs on 04-11-19.
//

#include "CarPositionBuffer.h"

void CarPositionBuffer::push(CarPosition carPosition) {
    cpBuffer[index] = carPosition;
    index = (index + 1) % size;
}

CarPosition CarPositionBuffer::at(int i) {
    i = (size + index - i - 1) % size;
    CarPosition cp = cpBuffer[i];
    return cp;
}
