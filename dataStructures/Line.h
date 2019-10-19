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

    Line(RowCol start, RowCol end, uchar color) : start(start), end(end), color(color) {
        a = (double) (end.row - start.row) / (end.col - start.col);
        b = (double) start.row + a * -start.col;
    };

    RowCol start;
    RowCol end;
    double a;
    double b;
    uchar color = 0;

    void draw(cv::Mat &image, int thickness) {
        int startRow = start.row < end.row ? start.row : end.row;
        int endRow = start.row < end.row ? end.row : start.row;
        for (int i = -thickness; i < thickness; i++) {
            this->draw(image, startRow, endRow, i);
        }
    }

    void draw(cv::Mat &image) {
        int startRow = start.row < end.row ? start.row : end.row;
        int endRow = start.row < end.row ? end.row : start.row;
        this->draw(image, startRow, endRow);
    }

    void draw(cv::Mat &image, int startRow, int endRow, int delta = 0) {
        if (!color) color = 255;

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

    double dist2ToPoint(int row, int col) {
        auto _col = (double) ((row - b) / a);
        auto _row = (double) (col * a + b);
        return (_col-col)*(_col-col) + (_row-row)*(_row-row);
    }

//    bool isCloseTo(Line &other) {
//       return true;
//    }
//
//    Line mergeLine(Line &other) {
//        return other;
//    }

    bool operator ==(Line &other) {
        return (this->start == other.start) && (this->end == other.end);
    }


};


#endif //SELFDRIVINGCAR_LINE_H
