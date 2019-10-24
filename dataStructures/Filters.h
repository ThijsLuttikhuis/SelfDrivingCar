//
// Created by thijs on 22-10-19.
//

#ifndef SELFDRIVINGCAR_FILTERS_H
#define SELFDRIVINGCAR_FILTERS_H

#include "RowCol.h"

struct Filters {
public:
    RowCol horizon;
    int minLineLength;
    int minDistToHorizon;
    int maxLineDistToHorizon;

    // thresholding image
    int thresholdMinimumDelta;
    int thresholdColDistance;

    Filters() = default;

};

#endif //SELFDRIVINGCAR_FILTERS_H

