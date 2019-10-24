//
// Created by thijs on 17-10-19.
//

#include <iostream>
#include "ImageProcessor.h"
#include "../utilities/Drawer.h"
#include "../dataStructures/Line.h"
#include "Segmentation.h"
#include "LineFinder.h"
#include "LinePositionFinder.h"
#include "RoadLine.h"

Segmentation ImageProcessor::segmentImage(bool showSegmentation) {
    Segmentation segmentation = Segmentation(image, showSegmentation, filters.thresholdMinimumDelta, filters.thresholdColDistance);
    segmentation.segmentImage(nThreads, filters.horizon.row, image.rows);
    return segmentation;
}

std::vector<Line> ImageProcessor::findLines(Segmentation* segmentation, bool showLines) {
    LineFinder lineFinder = LineFinder(image, filters, showLines);
    std::vector<Line> lines = lineFinder.findLines(segmentation);
   return lines;
}

void ImageProcessor::setFilters(Filters &_filters) {
    filters = _filters;
}

std::vector<RoadLine> ImageProcessor::getLinePositions(std::vector<Line>* lines) {
    LinePositionFinder linePositionFinder = LinePositionFinder(image);
    std::vector<RoadLine> lineCols = linePositionFinder.findLinePositions(lines);

    return lineCols;
}

