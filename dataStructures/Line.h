//
// Created by thijs on 19-10-19.
//

#ifndef SELFDRIVINGCAR_LINE_H
#define SELFDRIVINGCAR_LINE_H

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

#include "RowCol.h"
#include "../Drawer.h"

class Line {
public:
    Line() = default;

    Line(RowCol start, RowCol end) : start(start), end(end) {
        a = (double) (end.row - start.row) / (end.col - start.col);
        b = (double) start.row + a * -start.col;
    };

    RowCol start;
    RowCol end;
    double a;
    double b;
    static uchar color;

    void draw(cv::Mat &image, int thickness);

    void draw(cv::Mat &image);

    void draw(cv::Mat &image, int startRow, int endRow, int delta = 0);

    bool operator ==(Line &other) {
        return (this->start == other.start) && (this->end == other.end);
    }

    double dist2ToPoint(int row, int col);

    double length2();

    double dist2ToPoint(RowCol &point);
};


#endif //SELFDRIVINGCAR_LINE_H
