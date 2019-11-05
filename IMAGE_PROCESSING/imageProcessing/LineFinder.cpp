//
// Created by thijs on 22-10-19.
//

#include <iostream>
#include "LineFinder.h"
#include "../dataStructures/Pixel.h"

std::vector<Line> LineFinder::findLines(Segmentation* segmentation, CarPosition* carPosition) {
    std::vector<Line> lines;

    for (int row = filters.horizon.row; row < image.rows; row++) {
        const ColumnSegment &columnSegment = segmentation->segmentationRow[row];
        for (int col = 0; col < (int) columnSegment.col.size(); col++) {
            if (row < filters.horizon.row) continue;

            int edge = columnSegment.col[col];
            if (edge == RIGHT_EDGE || edge == LEFT_EDGE) {
                RowCol startOfLine = RowCol(row, col);

                // Create line
                std::vector<int> dRowDCol; // += 0 -> vertical, >0 -> line goes left, <0 -> line goes right
                RowCol endOfLine = recursiveSearch(segmentation, row + 1, col, edge, &dRowDCol);
                Line line = Line(startOfLine, endOfLine, dRowDCol);
                if (showLines == 3 && line.end.row != -1 && line.end.col != -1) {
                    uchar color = 100;
                    line.draw(image, 3, color);
                }
                // Filter line
                if (!filters.preLineFilter(line, lines)) continue;

                // Draw Line
                if (showLines == 3 && line.end.row != -1 && line.end.col != -1) {
                    uchar color = 100;
                    line.draw(image, 3, color);
                }

                // Add line
                lines.push_back(line);
            }
        }
    }

    RowCol newHorizonRC = filters.afterLineFilter(&lines);
    carPosition->carAngleToRoad = newHorizonRC.col - filters.horizon.col;

    // Draw lines
    if (showLines) {
        for (auto &line : lines) {
            if (showLines > 1) {
                line.draw(image, 7);
                line.draw(image, filters.horizon.row, image.rows);
            } else {
                line.draw(image, 1);
            }
        }
    }
    return lines;

}

RowCol LineFinder::recursiveSearch(Segmentation* segmentation, int _row, int _col, int _previousEdge,
                                   std::vector<int>* dColDRow) {
    // Magic (tm) - probably not wise to touch this function.

    int row = _row;
    int col = _col;

    int previousEdge = _previousEdge;
    int prevCol = _col;

    // Variable to check if we are at the end of the line
    int timeOut = -1;

    // Recursive while loop
    while (--timeOut != 0) {
        // If end of the image, return
        if (row <= 0 || row >= image.rows - 1 || col <= 0 || col >= image.cols - 1) {
            return {row, col};
        }

        // Get current pixel
        int edge = segmentation->segmentationRow[row].col[col];
        segmentation->segmentationRow[row].col[col] = UNDEFINED;

        // If we find the line, move one pixel down and continue
        if (edge == LEFT_EDGE || edge == RIGHT_EDGE) {
            timeOut = -1;
            previousEdge = edge;
            row++;
            dColDRow->push_back(col - prevCol);
            prevCol = col;
            continue;
        }
        // If we do not find a line, keep moving sideways to find it
        if (edge == NO_EDGE) {
            if (previousEdge == LEFT_EDGE || previousEdge == RIGHT_EDGE) {
                col += previousEdge;
                timeOut = maxTimeOut;
                previousEdge = previousEdge * -2;
                continue;
            } else if (previousEdge == NO_EDGE_GO_RIGHT || previousEdge == NO_EDGE_GO_LEFT) {
                col += previousEdge / -2;
                continue;
            }
        }
        if (edge == BETWEEN_EDGE) {
            if (previousEdge == LEFT_EDGE || previousEdge == RIGHT_EDGE) {
                col += previousEdge;
                previousEdge = previousEdge * 3;
                continue;
            } else if (previousEdge == BETWEEN_EDGE_GO_LEFT || previousEdge == BETWEEN_EDGE_GO_RIGHT) {
                col += static_cast<int>(previousEdge / 3);
                continue;
            }
        }

        // Else, a line probably already exists nearby
        return {-1, -1};
    }

    // End of line, return the line
    if (previousEdge == NO_EDGE_GO_RIGHT) {
        return {row, col - maxTimeOut};
    } else if (previousEdge == NO_EDGE_GO_LEFT) {
        return {row, col + maxTimeOut};
    } else {
        return {-1, -1};
    }
}
