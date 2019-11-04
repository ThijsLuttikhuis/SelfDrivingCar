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
    static const int size = 10;
    int index;
    CarPosition cpBuffer[size];

public:
    explicit CarPositionBuffer() : index(0) {

    };

    void push(CarPosition* carPosition);
    CarPosition at(int i);
};


#endif //SELFDRIVINGCAR_CARPOSITIONBUFFER_H
