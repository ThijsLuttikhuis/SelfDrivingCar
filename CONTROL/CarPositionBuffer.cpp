//
// Created by thijs on 04-11-19.
//

#include "CarPositionBuffer.h"

void CarPositionBuffer::push(CarPosition* carPosition) {
    CarPosition cp = *carPosition;
    std::cout << index << "  x  " << cpBuffer.size() << std::endl;
    cpBuffer.at(index) = cp;

    index = (index +1) % size;
}

CarPosition CarPositionBuffer::at(int i) {
    i = (size + index - i - 1) % size;
    return cpBuffer[i];
}
