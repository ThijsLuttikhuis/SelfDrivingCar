//
// Created by thijs on 17-10-19.
//

#include "ImageProcessor.h"
#include <thread>
#include "Drawer.h"
#include <iostream>

bool ImageProcessor::thresholdPixel(const cv::Vec3b &pixel) {
    bool left = ((pixel[0] > (&pixel)[-xDist][0] + minimumDelta) &&
                 (pixel[1] > (&pixel)[-xDist][1] + minimumDelta) &&
                 (pixel[2] > (&pixel)[-xDist][2] + minimumDelta));
    bool right = ((pixel[0] > (&pixel)[xDist][0] + minimumDelta) &&
                  (pixel[1] > (&pixel)[xDist][1] + minimumDelta) &&
                  (pixel[2] > (&pixel)[xDist][2] + minimumDelta));

    return left && right;
}

void ImageProcessor::thresholdColumn(ColumnSegment* columnSegment) {
    int cols = image.cols;
    const int &row = columnSegment->row;
    bool prev = false;
    uchar thresholdedColor[4] = {0, 127, 255, 191};
    for (int col = 0; col < cols-0; col++) {
        auto &pixel = image.at<cv::Vec3b>(row, col);
        if (thresholdPixel(pixel)) {
            if (!prev) {
                Drawer::setPixel(row, col, thresholdedColor[(int)PIXEL::LEFT_EDGE]);
                columnSegment->col.at(col) = PIXEL::LEFT_EDGE;
            }
            else {
                Drawer::setPixel(row, col, thresholdedColor[(int)PIXEL::BETWEEN_EDGE]);
                columnSegment->col.at(col) = PIXEL::BETWEEN_EDGE;
            }
            prev = true;
        }
        else {
            if (prev) {
                Drawer::setPixel(row, col, thresholdedColor[(int)PIXEL::RIGHT_EDGE]);
                columnSegment->col.at(col) = PIXEL::RIGHT_EDGE;
            }
            prev = false;
        }
    }
}

void ImageProcessor::segmentColumn(ColumnSegment* columnSegment) {
    const int &row = columnSegment->row;
    int &cols = image.cols;
    ColumnSegment colummSegment = ColumnSegment(row, cols);
    thresholdColumn(&colummSegment);
}

void* ImageProcessor::segmentationThread(void* arg) {
    // Get Thread Arguments
    ThreadArgs threadArgs = *(ThreadArgs*) arg;
    int &startRow = threadArgs.startRow;
    int &endRow = threadArgs.endRow;
    Segmentation* segmentation = threadArgs.segmentation;

    // Segmentation of columns
    for (int row = startRow; row < endRow; row++) {
        ColumnSegment columnSegment = segmentation->getRow(row);
        segmentColumn(&columnSegment);
        segmentation->setRow(columnSegment);
    }
}

Segmentation ImageProcessor::segmentImage() {
    int &rows = image.rows;
    int &cols = image.cols;
    Segmentation segmentation = Segmentation(rows, cols);

    // Init Thread arguments
    ThreadArgs targ[nThreads];
    std::thread tid[nThreads];

    for (int n = 0; n < nThreads; n++) {
        targ[n].startRow = n * rows / nThreads;
        targ[n].endRow = (n + 1) * rows / nThreads;
        targ[n].segmentation = &segmentation;

        tid[n] = std::thread(&ImageProcessor::segmentationThread, this, &targ[n]);
    }

    for (int n = 0; n < nThreads; n++) {
        tid[n].join();
    }

    return segmentation;
}
