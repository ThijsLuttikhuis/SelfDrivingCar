//
// Created by thijs on 17-10-19.
//

#include "ColumnSegment.h"

#ifndef SELFDRIVINGCAR_SEGMENTATION_H
#define SELFDRIVINGCAR_SEGMENTATION_H

class Segmentation {
    std::vector<ColumnSegment> row;
public:
    Segmentation(int _rows);

    ColumnSegment getRow(int row);
    void setRow(ColumnSegment columnSegment);
};

#endif //SELFDRIVINGCAR_SEGMENTATION_H
