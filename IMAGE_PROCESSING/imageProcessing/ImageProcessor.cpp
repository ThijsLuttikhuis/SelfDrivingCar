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
#include "../dataStructures/RoadLine.h"
#include "../../CarPosition.h"

Segmentation ImageProcessor::segmentImage(CarPosition* carPosition, bool showSegmentation) {
    Segmentation segmentation = Segmentation(image, showSegmentation, filters.thresholdMinimumDelta, filters.thresholdColDistance);
    segmentation.segmentImage(nThreads, filters.horizon.row, image.rows);

    return segmentation;
}

std::vector<Line> ImageProcessor::findLines(Segmentation* segmentation, CarPosition* carPosition, int showLines) {
    LineFinder lineFinder = LineFinder(image, filters, showLines);
    std::vector<Line> lines = lineFinder.findLines(segmentation, carPosition);

    return lines;
}

std::vector<RoadLine> ImageProcessor::getLinePositions(std::vector<Line>* lines, CarPosition* carPosition) {
    LinePositionFinder linePositionFinder = LinePositionFinder(image, filters);
    std::vector<RoadLine> roadLines = linePositionFinder.findLinePositions(lines);

    return roadLines;
}

CarPosition* ImageProcessor::getCarPosition(std::vector<RoadLine>* roadLines, CarPosition* carPosition, int showRoadLinePositions) {
    CarPositionFinder carPositionFinder = CarPositionFinder(image, filters, showRoadLinePositions);
    carPosition = carPositionFinder.findCarPosition(roadLines);

    return carPosition;
}

void ImageProcessor::setFilters(Filters &_filters) {
    filters = _filters;
}

