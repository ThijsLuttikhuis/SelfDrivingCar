//
// Created by thijs on 04-11-19.
//

#ifndef SELFDRIVINGCAR_CARPOSITIONBUFFER_H
#define SELFDRIVINGCAR_CARPOSITIONBUFFER_H


#include <vector>
#include <iostream>
#include "../CarPosition.h"

class CarPositionBuffer {
private:
    int size;
    int index;
    std::vector<CarPosition> cpBuffer;

public:
    explicit CarPositionBuffer(int size = 0) : size(size), index(1) {
        cpBuffer.resize(size, CarPosition());
    };

    void push(CarPosition* carPosition);
    CarPosition at(int i);
};


#endif //SELFDRIVINGCAR_CARPOSITIONBUFFER_H
