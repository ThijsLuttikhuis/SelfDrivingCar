//
// Created by thijs on 17-10-19.
//

#include <vector>

#ifndef SELFDRIVINGCAR_COLUMNSEGMENT_H
#define SELFDRIVINGCAR_COLUMNSEGMENT_H

class ColumnSegment {
public:
    explicit ColumnSegment(int row, int col) : row(row), col(std::vector<char>(col, false)) {}
    int row;
    std::vector<char> col;
};


#endif //SELFDRIVINGCAR_COLUMNSEGMENT_H
