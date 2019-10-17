//
// Created by thijs on 17-10-19.
//

#include <vector>

#ifndef SELFDRIVINGCAR_COLUMNSEGMENT_H
#define SELFDRIVINGCAR_COLUMNSEGMENT_H

class ColumnSegment {
public:
    explicit ColumnSegment(int row) : row(row) {}

    int row;
    std::vector<int> col;
};


#endif //SELFDRIVINGCAR_COLUMNSEGMENT_H
