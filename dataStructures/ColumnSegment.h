//
// Created by thijs on 17-10-19.
//

#include <vector>

#ifndef SELFDRIVINGCAR_COLUMNSEGMENT_H
#define SELFDRIVINGCAR_COLUMNSEGMENT_H

enum PIXEL : char {
    NO_EDGE = 0,
    BETWEEN_EDGE = 1,
    LEFT_EDGE = 2,
    RIGHT_EDGE = 3,

    NO_EDGE_GO_LEFT = 4,
    NO_EDGE_GO_RIGHT = 5,
    BETWEEN_EDGE_GO_LEFT = 6,
    BETWEEN_EDGE_GO_RIGHT = 7,

    UNDEFINED = 8
};

class ColumnSegment {
public:
    explicit ColumnSegment(int row, int col) : row(row), col(std::vector<PIXEL>(col, PIXEL::NO_EDGE)) {}
    int row;
    std::vector<PIXEL> col;
};


#endif //SELFDRIVINGCAR_COLUMNSEGMENT_H
