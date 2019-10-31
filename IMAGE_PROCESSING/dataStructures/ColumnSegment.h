//
// Created by thijs on 17-10-19.
//

#include <vector>
#include "Pixel.h"

#ifndef SELFDRIVINGCAR_COLUMNSEGMENT_H
#define SELFDRIVINGCAR_COLUMNSEGMENT_H

class ColumnSegment {
public:
    explicit ColumnSegment(int row, int col) : row(row), col(std::vector<PIXEL>(col, PIXEL::NO_EDGE)) {}
    int row;
    std::vector<PIXEL> col;
};


#endif //SELFDRIVINGCAR_COLUMNSEGMENT_H
