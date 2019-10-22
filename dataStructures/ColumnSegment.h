//
// Created by thijs on 17-10-19.
//

#include <vector>

#ifndef SELFDRIVINGCAR_COLUMNSEGMENT_H
#define SELFDRIVINGCAR_COLUMNSEGMENT_H

enum PIXEL : char {
    // Dont touch the numbers!

    BETWEEN_EDGE_GO_LEFT = -3,
    NO_EDGE_GO_LEFT = 2,

    LEFT_EDGE = -1,
    BETWEEN_EDGE = 0,
    RIGHT_EDGE = 1,

    NO_EDGE_GO_RIGHT = -2,
    BETWEEN_EDGE_GO_RIGHT = 3,

    NO_EDGE = 63,
    UNDEFINED = 127
};

class ColumnSegment {
public:
    explicit ColumnSegment(int row, int col) : row(row), col(std::vector<PIXEL>(col, PIXEL::NO_EDGE)) {}
    int row;
    std::vector<PIXEL> col;
};


#endif //SELFDRIVINGCAR_COLUMNSEGMENT_H
