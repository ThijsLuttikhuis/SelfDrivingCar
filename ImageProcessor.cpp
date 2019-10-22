//
// Created by thijs on 17-10-19.
//

#include "ImageProcessor.h"
#include "Drawer.h"
#include "dataStructures/Line.h"
#include "dataStructures/Segmentation.h"
#include "dataStructures/LineFinder.h"

Segmentation ImageProcessor::segmentImage(bool showSegmentation) {
    Segmentation segmentation = Segmentation(image, showSegmentation);
    segmentation.segmentImage(nThreads, horizon.row, image.rows);
    return segmentation;
}

std::vector<Line> ImageProcessor::findLines(Segmentation* segmentation) {
    LineFinder lineFinder = LineFinder(image, minLineLength, horizon, minDistToHorizon, maxLineDistToHorizon);
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

