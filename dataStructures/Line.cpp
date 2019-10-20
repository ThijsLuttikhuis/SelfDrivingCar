//
// Created by thijs on 19-10-19.
//

#include "Line.h"

uchar Line::color = 0;

void Line::draw(cv::Mat &image, int thickness) {
    int startRow = start.row < end.row ? start.row : end.row;
    int endRow = start.row < end.row ? end.row : start.row;
    for (int i = -thickness; i < thickness; i++) {
        this->draw(image, startRow, endRow, i);
    }
}

void Line::draw(cv::Mat &image) {
    int startRow = start.row < end.row ? start.row : end.row;
    int endRow = start.row < end.row ? end.row : start.row;
    this->draw(image, startRow, endRow);
}

void Line::draw(cv::Mat &image, int startRow, int endRow, int delta) {
    color = 255;

    for (int row = startRow; row < endRow; row++) {
        auto col = (int) ((row - b) / a) + delta;
        if (col >= 0 && col < image.cols) {
            Drawer::setPixel(row, col, color);
        }
    }
    for (int col = 0; col < image.cols; col++) {
        auto row = (int) (col * a + b);
        if (row >= startRow && row < endRow) {
            Drawer::setPixel(row, col, color);
        }
    }
}

double Line::dist2ToPoint(RowCol &point) {
    return dist2ToPoint(point.row, point.col);
}

double Line::dist2ToPoint(int row, int col) {
    auto _colC = (double) ((row - b) / a);
    auto _rowC = (double) (_colC * a + b);

//    auto _rowR = (double) (col * a + b);
//    auto _colR = (double) ((_rowR - b) / a);

    //Drawer::setPixel(_rowC, _colC, 50);
    //Drawer::setPixel(_rowR, _colR, 80);

    return (_colC-col)*(_colC-col) + (_rowC-row)*(_rowC -row);
}

double Line::length2() {
    return start.dist2(end);
}
