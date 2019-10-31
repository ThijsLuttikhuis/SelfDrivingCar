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
                if (!filters.preFilter(startOfLine)) continue;

                // Create line
                std::vector<int> dRowDCol; // += 0 -> vertical, >0 -> line goes left, <0 -> line goes right
                RowCol endOfLine = recursiveSearch(segmentation, row + 1, col, edge, &dRowDCol);
                Line line = Line(startOfLine, endOfLine);

                // Filters after
                if (!filters.lineFilter(line, lines, &dRowDCol)) continue;

                // draw line
                if (showLines) {
                    if (showLines > 1) {
                        line.draw(image, 7);
                        line.draw(image, filters.horizon.row, image.rows);
                    }
                    else {
                        line.draw(image, 1);
                    }
                }
                lines.push_back(line);
            }
        }
    }
    return lines;
}

RowCol LineFinder::recursiveSearch(Segmentation* segmentation, int _row, int _col, PIXEL _previousEdge,
                                   std::vector<int>* dColDRow) {
    // Magic (tm) - probably not wise to touch this function.
    PIXEL previousEdge = _previousEdge;
    int row = _row;
    int col = _col;

    int prevRow = _row;
    int prevCol = _col;


    int index = 0;
    int timeOut = -1;

    while (--timeOut != 0) {
        if (row <= 0 || row >= image.rows - 1 || col <= 0 || col >= image.cols - 1) {
            return {row, col};
        }

        PIXEL edge = segmentation->segmentationRow[row].col[col];
        segmentation->segmentationRow[row].col[col] = PIXEL::UNDEFINED;
        if (edge == PIXEL::LEFT_EDGE || edge == PIXEL::RIGHT_EDGE) {
            timeOut = -1;
            previousEdge = edge;
            row++;
            dColDRow->push_back(col - prevCol);
            prevRow = row;
            prevCol = col;
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
