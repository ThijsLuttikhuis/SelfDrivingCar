//
// Created by thijs on 17-10-19.
//

#include <iostream>
#include "ImageProcessor.h"
#include "Drawer.h"
#include "dataStructures/Line.h"
#include "dataStructures/Segmentation.h"

Segmentation ImageProcessor::segmentImage(bool showSegmentation) {
    Segmentation segmentation = Segmentation(image, showSegmentation);
    segmentation.segmentImage(nThreads, horizon.row, image.rows);
    return segmentation;
}

RowCol ImageProcessor::recursiveSearch(Segmentation* segmentation, int row, int col, PIXEL previousEdge, int timeOut = -1) {

    if (row == 0 || row == image.rows-1 || col == 0 || col == image.cols-1) {
        return {row, col};
    }

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

    PIXEL edge = segmentation->segmentationRow[row].col[col];
    segmentation->segmentationRow[row].col[col] = PIXEL::UNDEFINED;

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

std::vector<Line> ImageProcessor::findLines(Segmentation* segmentation, double minLineLength) {
    std::vector<Line> lines;

    for (int row = horizon.row; row < image.rows; row++) {
        const ColumnSegment &columnSegment = segmentation->segmentationRow[row];
        for (int col = 0; col < (int)columnSegment.col.size(); col++) {
            if (row < horizon.row) continue;

            PIXEL edge = columnSegment.col[col];
            if (edge == PIXEL::RIGHT_EDGE || edge == PIXEL::LEFT_EDGE) {
                RowCol startOfLine = RowCol(row, col);

                // Filters before
                if (startOfLine.dist2(horizon) < minLineSegmentDistToHorizon) continue;

                RowCol endOfLine = recursiveSearch(segmentation, row + 1, col, edge);
                // Create line
                Line line = Line(startOfLine, endOfLine);

                // Filters after
                if (line.end.row == -1 || line.end.col == -1) continue;

                // Filter line length
                if (line.length2() < minLineLength*minLineLength) continue;

                // Fiter direction of the line (towards horizon point)
                double distanceToHorizon = line.dist2ToPoint(horizon); // left ==> dth < 0
                if (distanceToHorizon > maxLineDistToHorizon*maxLineDistToHorizon) continue;

                bool isCloseToOtherLine = false;
                for (auto &otherLine : lines) {
                    if (otherLine.start.dist2(line.start) < 30 && otherLine.end.dist2(line.end) < 30) {
                        isCloseToOtherLine = true;
                        break;
                    }
                }
                if (isCloseToOtherLine) continue;

                // Make and draw line
                line.draw(image, 7);
                line.draw(image, horizon.row, image.rows);
                lines.push_back(line);
                //Drawer::showImage(image, true);
            }
        }
    }
    std::cout << lines.size() << " lines found!" << std::endl;
    return lines;
}

void ImageProcessor::setHorizon(RowCol _horizon, int _minLineSegmentDistToHorizon, int _minRatioLineSegmentDistToHorizon, int _maxLineDistToHorizon) {
    horizon = _horizon;
    minLineSegmentDistToHorizon = _minLineSegmentDistToHorizon;
    minRatioLineSegmentDistToHorizon = _minRatioLineSegmentDistToHorizon;
    maxLineDistToHorizon = _maxLineDistToHorizon;
}

