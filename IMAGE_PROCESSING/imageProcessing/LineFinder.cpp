//
// Created by thijs on 22-10-19.
//

#include "LineFinder.h"
#include "../dataStructures/Pixel.h"


std::vector<Line> LineFinder::findLines(Segmentation* segmentation) {
    std::vector<Line> lines;

    for (int row = filters.horizon.row; row < image.rows; row++) {
        const ColumnSegment &columnSegment = segmentation->segmentationRow[row];
        for (int col = 0; col < (int) columnSegment.col.size(); col++) {
            if (row < filters.horizon.row) continue;

            int edge = columnSegment.col[col];
            if (edge == RIGHT_EDGE || edge == LEFT_EDGE) {
                RowCol startOfLine = RowCol(row, col);

                // Filters before
                if (!filters.preFilter(startOfLine)) continue;

                // Create line
                std::vector<int> dRowDCol; // += 0 -> vertical, >0 -> line goes left, <0 -> line goes right
                RowCol endOfLine = recursiveSearch(segmentation, row + 1, col, edge, &dRowDCol);
                Line line = Line(startOfLine, endOfLine);

                // Filters after
                if (!filters.lineFilter(line, lines, &dRowDCol)) {
                    if (showLines == 3 && line.end.row != -1 && line.end.col != -1) {
                        line.color = 100;
                        line.draw(image, 3);
                    }
                    continue;
                }

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

                line.dRowDCol = dRowDCol;
                lines.push_back(line);
            }
        }
    }
    return lines;
}

RowCol LineFinder::recursiveSearch(Segmentation* segmentation, int _row, int _col, int _previousEdge,
                                   std::vector<int>* dColDRow) {
    // Magic (tm) - probably not wise to touch this function.
    int previousEdge = _previousEdge;
    int row = _row;
    int col = _col;

    int prevCol = _col;


    int timeOut = -1;

    while (--timeOut != 0) {
        if (row <= 0 || row >= image.rows - 1 || col <= 0 || col >= image.cols - 1) {
            return {row, col};
        }

        int edge = segmentation->segmentationRow[row].col[col];
        segmentation->segmentationRow[row].col[col] = UNDEFINED;
        if (edge == LEFT_EDGE || edge == RIGHT_EDGE) {
            timeOut = -1;
            previousEdge = edge;
            row++;
            dColDRow->push_back(col - prevCol);
            prevCol = col;
            continue;
        }
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
        return {-1, -1};
    }

    if (previousEdge == NO_EDGE_GO_RIGHT) {
        return {row, col - maxTimeOut};
    } else if (previousEdge == NO_EDGE_GO_LEFT) {
        return {row, col + maxTimeOut};
    } else {
        return {-1, -1};
    }
}
