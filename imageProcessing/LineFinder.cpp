//
// Created by thijs on 22-10-19.
//

#include "LineFinder.h"
#include <iostream>


std::vector<Line> LineFinder::findLines(Segmentation* segmentation) {
    std::vector<Line> lines;

    for (int row = filters.horizon.row; row < image.rows; row++) {
        const ColumnSegment &columnSegment = segmentation->segmentationRow[row];
        for (int col = 0; col < (int) columnSegment.col.size(); col++) {
            if (row < filters.horizon.row) continue;

            PIXEL edge = columnSegment.col[col];
            if (edge == PIXEL::RIGHT_EDGE || edge == PIXEL::LEFT_EDGE) {
                RowCol startOfLine = RowCol(row, col);

                // Filters before
                if (!preFilter(startOfLine)) continue;

                // Create line
                std::vector<double> dRowDCol; // += 0 -> vertical, >0 -> line goes left, <0 -> line goes right
                RowCol endOfLine = recursiveSearch(segmentation, row + 1, col, edge, &dRowDCol);
                Line line = Line(startOfLine, endOfLine);

                // Filters after
                if (!lineFilter(line, lines, &dRowDCol)) continue;

                // draw line
                if (showLines) {
                    line.draw(image, 7);
                    line.draw(image, filters.horizon.row, image.rows);
                    //Drawer::showImage(image, true);
                }
                lines.push_back(line);
            }
        }
    }
    return lines;
}

RowCol LineFinder::recursiveSearch(Segmentation* segmentation, int _row, int _col, PIXEL _previousEdge,
                                   std::vector<double>* dColDRow) {
    // Magic (tm) - probably not wise to touch this function.
    PIXEL previousEdge = _previousEdge;
    int row = _row;
    int col = _col;

    int prevRow = _row;
    int prevCol = _col;


    int index = 0;
    int timeOut = -1;

    while (--timeOut != 0) {
        if (row == 0 || row == image.rows - 1 || col == 0 || col == image.cols - 1) {
            return {row, col};
        }

        PIXEL edge = segmentation->segmentationRow[row].col[col];
        segmentation->segmentationRow[row].col[col] = PIXEL::UNDEFINED;
        if (edge == PIXEL::LEFT_EDGE || edge == PIXEL::RIGHT_EDGE) {
            timeOut = -1;
            previousEdge = edge;
            row++;
            if (++index % 5 == 0) {
                dColDRow->push_back((double)(col - prevCol) /  (row - prevRow));
                prevRow = row;
                prevCol = col;
            }
            continue;
        }
        if (edge == PIXEL::NO_EDGE) {
            if (previousEdge == PIXEL::LEFT_EDGE || previousEdge == PIXEL::RIGHT_EDGE) {
                col += static_cast<char>(previousEdge);
                timeOut = maxTimeOut;
                previousEdge = static_cast<PIXEL>(previousEdge * -2);
                continue;
            } else if (previousEdge == PIXEL::NO_EDGE_GO_RIGHT || previousEdge == PIXEL::NO_EDGE_GO_LEFT) {
                col += static_cast<char>(previousEdge / -2);
                continue;
            }
        }
        if (edge == PIXEL::BETWEEN_EDGE) {
            if (previousEdge == PIXEL::LEFT_EDGE || previousEdge == PIXEL::RIGHT_EDGE) {
                col += static_cast<char>(previousEdge);
                previousEdge = static_cast<PIXEL>(previousEdge * 3);
                continue;
            } else {
                col += static_cast<char>(previousEdge / 3);
                continue;
            }
        }
        return {-1, -1};
    }

    if (previousEdge == PIXEL::NO_EDGE_GO_RIGHT) {
        return {row, col - maxTimeOut};
    } else if (previousEdge == PIXEL::NO_EDGE_GO_LEFT) {
        return {row, col + maxTimeOut};
    } else {
        return {-1, -1};
    }
}

bool LineFinder::preFilter(const RowCol &startOfLine) {
    // filter lines too close to the horizon
    if (startOfLine.dist2(filters.horizon) < filters.minDistToHorizon) return false;

    return true;
}

bool LineFinder::lineFilter(Line &line, const std::vector<Line> &otherLines, const std::vector<double>* dColDRow) {


    // Filters after
    if (line.end.row == -1 || line.end.col == -1) return false;

    // Filter line length
    if (line.length2() < filters.minLineLength * filters.minLineLength) return false;

    // Fiter direction of the line (towards horizon point)
    double distanceToHorizon = line.horizontalDist2ToPoint(filters.horizon); // left ==> dth < 0
    if (distanceToHorizon > filters.maxLineDistToHorizon * filters.maxLineDistToHorizon) {
        // Actually fine, if the line is long enough, but line is not straight, or the car is not straight.
        if (line.length2() < filters.minLineLength*filters.minLineLength*2*2) return false;
        line.isCurved = true;
        return false;
    }

    // Filter if another line is already very close
    bool isCloseToOtherLine = false;
    for (auto &otherLine : otherLines) {
        if (otherLine.start.dist2(line.start) < 6 * 6 && otherLine.end.dist2(line.end) < 6 * 6) {
            isCloseToOtherLine = true;
            break;
        }
    }
    if (isCloseToOtherLine) return false;

    return true;
}