//
// Created by thijs on 17-10-19.
//

#include "Segmentation.h"

ColumnSegment Segmentation::getRow(int _row) {
    return this->row[_row];
}

void Segmentation::setRow(ColumnSegment columnSegment) {
    int _row = columnSegment.row;
    this->row[_row] = columnSegment;
}

Segmentation::Segmentation(int _rows, int _cols) {
    for (int _row = 0; _row < _rows; _row++) {
        ColumnSegment columnSegment = ColumnSegment(_row, _cols);
        this->row.emplace_back(columnSegment);
    }
}
