//
// Created by thijs on 23-10-19.
//

#ifndef SELFDRIVINGCAR_ROADLINE_H
#define SELFDRIVINGCAR_ROADLINE_H


#include "../dataStructures/Line.h"

class RoadLine {
public:
    double lineColAtCar;
    std::vector<Line> correspondingLines;


    void drawSquareAtColumn(cv::Mat &image, int size = 20);
};


#endif //SELFDRIVINGCAR_ROADLINE_H
