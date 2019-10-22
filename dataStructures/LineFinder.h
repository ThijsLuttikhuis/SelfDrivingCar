//
// Created by thijs on 22-10-19.
//

#ifndef SELFDRIVINGCAR_LINEFINDER_H
#define SELFDRIVINGCAR_LINEFINDER_H


#include "RowCol.h"
#include <vector>
#include "Line.h"
#include "Segmentation.h"

class LineFinder {
private:
    int maxTimeOut = 8;

    cv::Mat &image;
    int minLineLength;
    RowCol horizon;
    int minDistToHorizon;
    int maxLineDistToHorizon;

public:
    LineFinder(cv::Mat &image, int minLineLength, RowCol horizon, int minDistToHorizon, int maxLineDistToHorizon) :
    image(image), minLineLength(minLineLength), horizon(horizon),
    minDistToHorizon(minDistToHorizon), maxLineDistToHorizon(maxLineDistToHorizon) {};


    std::vector<Line> findLines(Segmentation* segmentation);

    RowCol recursiveSearch(Segmentation* segmentation, int row, int col, PIXEL previousEdge, int timeOut);
};


#endif //SELFDRIVINGCAR_LINEFINDER_H
