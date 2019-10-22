//
// Created by thijs on 22-10-19.
//

#ifndef SELFDRIVINGCAR_FILTERS_H
#define SELFDRIVINGCAR_FILTERS_H

#endif //SELFDRIVINGCAR_FILTERS_H

#include "RowCol.h"

struct Filters {
public:
    RowCol horizon;
    int minLineLength;
    int minDistToHorizon;
    int maxLineDistToHorizon;

    Filters() : Filters({}, 0, 0, 0) {};
    Filters(RowCol horizon, int minLineLength, int minDistToHorizon, int maxLineDistToHorizon) :
          horizon(horizon), minLineLength(minLineLength), minDistToHorizon(minDistToHorizon), maxLineDistToHorizon(maxLineDistToHorizon) {};
};
