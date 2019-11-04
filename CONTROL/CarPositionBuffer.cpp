//
// Created by thijs on 04-11-19.
//

#include "CarPositionBuffer.h"

void CarPositionBuffer::push(CarPosition* carPosition) {
    if (!carPosition) return;
    CarPosition cp = *carPosition;
    cpBuffer.at(index) = cp;
    index = (index +1) % size;
}

CarPosition CarPositionBuffer::at(int i) {
    i = (size + index - i - 1) % size;
    std::cout << i << std::endl;
    std::cout << "size: " << cpBuffer.size() << std::endl;
    return cpBuffer.at(i);
}
