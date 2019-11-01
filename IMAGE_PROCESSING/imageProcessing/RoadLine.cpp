//
// Created by thijs on 23-10-19.
//

#include "RoadLine.h"

void RoadLine::drawSquareAtColumn(cv::Mat &image, int size) {
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