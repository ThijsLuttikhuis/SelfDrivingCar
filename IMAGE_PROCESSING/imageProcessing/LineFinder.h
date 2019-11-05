//
// Created by thijs on 22-10-19.
//

#ifndef SELFDRIVINGCAR_LINEFINDER_H
#define SELFDRIVINGCAR_LINEFINDER_H

#include "../dataStructures/RowCol.h"
#include <vector>
#include "../dataStructures/Line.h"
#include "Segmentation.h"
#include "../dataStructures/Filters.h"
#include "../../CarPosition.h"


class LineFinder {
private:
    cv::Mat &image;
    Filters &filters;

    int maxTimeOut = 8;
    int showLines;

    RowCol recursiveSearch(Segmentation* segmentation, int row, int col, int previousEdge, std::vector<int>* dColDRow);

public:
    LineFinder(cv::Mat &image, Filters &filters, int showLines) :
          image(image), filters(filters), showLines(showLines) {};

    std::vector<Line> findLines(Segmentation* segmentation, CarPosition* carPosition);
};

#endif //SELFDRIVINGCAR_LINEFINDER_H
