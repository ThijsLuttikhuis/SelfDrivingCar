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
    segmentation.segmentImage(nThreads, horizon.row, image.rows);
    return segmentation;
}

std::vector<Line> ImageProcessor::findLines(Segmentation* segmentation, bool showLines) {
    Filters filters = {horizon, minLineLength, minDistToHorizon, maxLineDistToHorizon};
    LineFinder lineFinder = LineFinder(image, filters, showLines);
    std::vector<Line> lines = lineFinder.findLines(segmentation);
   return lines;
}

void ImageProcessor::setHorizon(RowCol _horizon, int _minLineSegmentDistToHorizon, int _maxLineDistToHorizon) {
    horizon = _horizon;
    minDistToHorizon = _minLineSegmentDistToHorizon;
    maxLineDistToHorizon = _maxLineDistToHorizon;
}

void ImageProcessor::setMinLineLength(int _minLineLength) {
    minLineLength = _minLineLength;
}

std::vector<RowCol> ImageProcessor::getLinePositions(std::vector<Line>* lines) {

    return std::vector<RowCol>();
}

