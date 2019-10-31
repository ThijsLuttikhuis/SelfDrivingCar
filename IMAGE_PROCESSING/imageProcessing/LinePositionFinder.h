//
// Created by thijs on 23-10-19.
//

#ifndef SELFDRIVINGCAR_LINEPOSITIONFINDER_H
#define SELFDRIVINGCAR_LINEPOSITIONFINDER_H

#include <opencv2/core/mat.hpp>
#include "../dataStructures/Line.h"
#include "RoadLine.h"
#include <vector>

class LinePositionFinder {
private:
    cv::Mat &image;

public:
    explicit LinePositionFinder(cv::Mat &image) : image(image) {};


    std::vector<RoadLine> findLinePositions(std::vector<Line>* lines);
};


#endif //SELFDRIVINGCAR_LINEPOSITIONFINDER_H
