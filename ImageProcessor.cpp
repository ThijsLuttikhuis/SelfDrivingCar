//
// Created by thijs on 17-10-19.
//

#include <iostream>
#include "ImageProcessor.h"
#include "Drawer.h"
#include "dataStructures/Line.h"
#include "dataStructures/Segmentation.h"

Segmentation ImageProcessor::segmentImage() {
    Segmentation segmentation = Segmentation(image);
    segmentation.segmentImage(nThreads);
    return segmentation;
}

RowCol ImageProcessor::recursiveSearch(Segmentation* segmentation, int row, int col, PIXEL previousEdge, int timeOut = -1) {
    if (--timeOut == 0) {
        if (previousEdge == PIXEL::NO_EDGE_GO_RIGHT) {
            return {row, col-maxTimeOut};
        }
        if (previousEdge == PIXEL::NO_EDGE_GO_LEFT) {
            return {row, col+maxTimeOut};
        }
        else {
            return {-1,-1};
        }
    }

    PIXEL edge = segmentation->getRow(row).col[col];
    segmentation->getRow(row).col[col] = PIXEL::NO_EDGE;

    if (edge == PIXEL::LEFT_EDGE) {
        return recursiveSearch(segmentation, row+1, col, PIXEL::LEFT_EDGE);
    }
    if (edge == PIXEL::RIGHT_EDGE) {
        return recursiveSearch(segmentation, row+1, col, PIXEL::RIGHT_EDGE);
    }
    if (edge == PIXEL::NO_EDGE) {
        if (previousEdge == PIXEL::LEFT_EDGE) {
            return recursiveSearch(segmentation, row, col+1, PIXEL::NO_EDGE_GO_RIGHT, maxTimeOut);
        }
        if (previousEdge == PIXEL::RIGHT_EDGE) {
            return recursiveSearch(segmentation, row, col-1, PIXEL::NO_EDGE_GO_LEFT, maxTimeOut);
        }
        if (previousEdge == PIXEL::NO_EDGE_GO_RIGHT) {
            return recursiveSearch(segmentation, row, col+1, PIXEL::NO_EDGE_GO_RIGHT, timeOut);
        }
        if (previousEdge == PIXEL::NO_EDGE_GO_LEFT) {
            return recursiveSearch(segmentation, row, col-1, PIXEL::NO_EDGE_GO_LEFT, timeOut);
        }
    }
    if (edge == PIXEL::BETWEEN_EDGE) {
        if (previousEdge == PIXEL::LEFT_EDGE) {
            return recursiveSearch(segmentation, row, col-1, PIXEL::BETWEEN_EDGE_GO_LEFT);
        }
        if (previousEdge == PIXEL::RIGHT_EDGE) {
            return recursiveSearch(segmentation, row, col+1, PIXEL::BETWEEN_EDGE_GO_RIGHT);
        }
        if (previousEdge == PIXEL::BETWEEN_EDGE_GO_RIGHT) {
            return recursiveSearch(segmentation, row, col+1, PIXEL::BETWEEN_EDGE_GO_RIGHT);
        }
        if (previousEdge == PIXEL::BETWEEN_EDGE_GO_LEFT) {
            return recursiveSearch(segmentation, row, col-1, PIXEL::BETWEEN_EDGE_GO_LEFT);
        }
    }
    return {-1, -1};

}

std::vector<Line> ImageProcessor::findLines(Segmentation* segmentation) {
    std::vector<Line> lines;
    for (int row = 0; row < image.rows; row++) {

        const ColumnSegment &columnSegment = segmentation->getRow(row);
        for (int col = 0; col < (int)columnSegment.col.size(); col++) {
            PIXEL edge = columnSegment.col[col];

            if (edge == PIXEL::RIGHT_EDGE || edge == PIXEL::LEFT_EDGE) {

                RowCol startOfLine = RowCol(row, col);
                RowCol endOfLine = recursiveSearch(segmentation, row + 1, col, edge, -1);
                if (endOfLine.row == -1) continue;

                Line line = Line(startOfLine, endOfLine);
                line.draw(image);
                lines.push_back(line);
               // Drawer::showImage(image, false);
            }
        }
    }

    return lines;
}


