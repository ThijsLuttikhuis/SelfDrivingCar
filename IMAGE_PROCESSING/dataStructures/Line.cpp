//
// Created by thijs on 19-10-19.
//

#include "Line.h"

void Line::draw(const cv::Mat &image, int thickness, uchar color) const {
    int startRow = start.row < end.row ? start.row : end.row;
    int endRow = start.row < end.row ? end.row : start.row;
    for (int i = -thickness; i < thickness; i++) {
        this->draw(image, startRow, endRow, i, color);
    }
}

void Line::draw(const cv::Mat &image, uchar color) const {
    int startRow = start.row < end.row ? start.row : end.row;
    int endRow = start.row < end.row ? end.row : start.row;
    this->draw(image, startRow, endRow, color);
}

void Line::draw(const cv::Mat &image, int startRow, int endRow, int delta, uchar color) const {
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

double Line::horizontalDist2ToPoint(RowCol &point) const {
    return dist2ToPoint(point.row, point.col);
}

double Line::dist2ToPoint(int row, int col) const {
    auto _colC = (double) ((row - b) / a);
    auto _rowC = (double) (col * a + b);
    return (_colC-col)*(_colC-col) + (_rowC-row)*(_rowC-row);
}

double Line::length2() const {
    return start.dist2(end);
}

double Line::getColAtRow(int row) const {
   // if (a == 0) return -1;
    return (double) ((row - b) / a);
}

double Line::getRowAtCol(int col) const {
    return (double (col * a + b));
}

int Line::verticalLength() const {
    return end.row - start.row;
}
