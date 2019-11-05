//
// Created by thijs on 31-10-19.
//

#ifndef SELFDRIVINGCAR_CARPOSITIONFINDER_H
#define SELFDRIVINGCAR_CARPOSITIONFINDER_H

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include "../../CarPosition.h"
#include "../dataStructures/Filters.h"
#include "../dataStructures/RoadLine.h"

class CarPositionFinder {
private:
    cv::Mat &image;
    Filters &filters;
    int showRoadLinePositions;

public:
    CarPositionFinder(cv::Mat &image, Filters &filters, int showRoadLinePositions) :
          image(image), filters(filters), showRoadLinePositions(showRoadLinePositions) {};

    CarPosition* findCarPosition(std::vector<RoadLine>* roadLines);
};


#endif //SELFDRIVINGCAR_CARPOSITIONFINDER_H
