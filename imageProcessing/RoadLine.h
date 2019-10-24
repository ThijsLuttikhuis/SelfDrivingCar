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

    void drawColumn(cv::Mat &image) {
        int size = 20;

        auto col = lineColAtCar;
        auto row = image.rows - size - 1;
        for (int i = -size; i < size; i++) {
            for (int j = -size; j < size; j++) {
                uchar color = 100;
                auto _col = (int)col + i;
                auto _row = (int)row + j;
                if (_col > 0 && _col < image.cols && _row > 0 && _row < image.rows) {
                    Drawer::setPixel(_row, _col, color);
                }
            }
        }
    }

};


#endif //SELFDRIVINGCAR_ROADLINE_H
