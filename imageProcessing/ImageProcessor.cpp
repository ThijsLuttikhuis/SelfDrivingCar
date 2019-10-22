//
// Created by thijs on 17-10-19.
//

#include "ImageProcessor.h"
#include "../utilities/Drawer.h"
#include "../dataStructures/Line.h"
#include "Segmentation.h"
#include "LineFinder.h"

Segmentation ImageProcessor::segmentImage(bool showSegmentation) {
    Segmentation segmentation = Segmentation(image, showSegmentation);
    segmentation.segmentImage(nThreads, filters.horizon.row, image.rows);
    return segmentation;
}

std::vector<Line> ImageProcessor::findLines(Segmentation* segmentation, bool showLines) {
    LineFinder lineFinder = LineFinder(image, filters, showLines);
    std::vector<Line> lines = lineFinder.findLines(segmentation);
   return lines;
}

void ImageProcessor::setHorizon(RowCol horizon, int minDistToHorizon, int maxLineDistToHorizon) {
    filters.horizon = horizon;
    filters.minDistToHorizon = minDistToHorizon;
    filters.maxLineDistToHorizon = maxLineDistToHorizon;
}

void ImageProcessor::setMinLineLength(int minLineLength) {
    filters.minLineLength = minLineLength;
}

std::vector<RowCol> ImageProcessor::getLinePositions(std::vector<Line>* lines) {

    return std::vector<RowCol>();
}

