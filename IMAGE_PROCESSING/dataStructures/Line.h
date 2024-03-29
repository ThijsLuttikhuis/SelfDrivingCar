//
// Created by thijs on 19-10-19.
//

#ifndef SELFDRIVINGCAR_LINE_H
#define SELFDRIVINGCAR_LINE_H

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <utility>

#include "RowCol.h"
#include "../utilities/Drawer.h"

class Line {
public:
    Line() : Line({}, {}) { };

    Line(RowCol start, RowCol end) : Line(start, end , {}) { };

    Line(RowCol start, RowCol end, std::vector<int> dRowDCol) : start(start), end(end), dRowDCol(std::move(dRowDCol)) {
        if (end.col == start.col) {
            a = (double) 99999;
            b = (double) start.row + a * -start.col;
        }
        else {
            a = (double) (end.row - start.row) / (end.col - start.col);
            b = (double) start.row + a * -start.col;
        }

    };

    RowCol start;
    RowCol end;
    double a;
    double b;

    bool isCurved = false;
    std::vector<int> dRowDCol;

    void draw(const cv::Mat &image, int thickness, uchar color = 255) const;

    void draw(const cv::Mat &image, uchar color = 255) const;

    void draw(const cv::Mat &image, int startRow, int endRow, int delta = 0, uchar color = 255) const;

    bool operator ==(const Line &other) const {
        return (this->start == other.start) && (this->end == other.end);
    }

    double dist2ToPoint(int row, int col) const;

    double length2() const;

    int verticalLength() const;

    double horizontalDist2ToPoint(RowCol &point) const;

    double getColAtRow(int row) const;

    double getRowAtCol(int col) const;

};


#endif //SELFDRIVINGCAR_LINE_H
