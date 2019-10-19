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
    cv::Vec3b thresholdedColor[4] = {cv::Vec3b(63, 63, 127),
                                     cv::Vec3b(63, 63, 0),
                                     cv::Vec3b(0,0,0),
                                     cv::Vec3b(255,255,255)};
    for (int col = 0; col < cols-0; col++) {
        auto &pixel = image.at<cv::Vec3b>(row, col);
        if (thresholdPixel(pixel)) {
            if (!prev) {
                Drawer::setPixel(row, col, thresholdedColor[0]);
                columnSegment->col.at(col) = true;
            }
            else {
                Drawer::setPixel(row, col, thresholdedColor[3]);
            }
            prev = true;
        }
        else {
            if (prev) {
                Drawer::setPixel(row, col, thresholdedColor[1]);
                columnSegment->col.at(col) = true;
            }
            else {
                Drawer::setPixel(row, col, thresholdedColor[2]);
            }
            prev = false;
        }
    }
}

void ImageProcessor::groupColumnSegment(ColumnSegment* columnSegment) {
//    const int &row = columnSegment->row;
//    cv::Vec3b red = cv::Vec3b(255, 0, 255);
//    cv::Vec3b green = cv::Vec3b(255, 255, 0);
//
//    for (int col = 1; col < image.cols-1; col++) {
//        if (columnSegment->col.at(col)) {
//            if (!columnSegment->col.at(col+1)) {
//                auto &pixel = image.at<cv::Vec3b>(row, col);
//                Drawer::setPixel(pixel, red);
//            }
//            else if (!columnSegment->col.at(col-1)) {
//                auto &pixel = image.at<cv::Vec3b>(row, col);
//                Drawer::setPixel(pixel, green);
//            }
//            else {
//                columnSegment->col.at(col) = 2;
//            }
//        }
//    }
}

void ImageProcessor::segmentColumn(ColumnSegment* columnSegment) {
    const int &row = columnSegment->row;
    int &cols = image.cols;
    ColumnSegment colummSegment = ColumnSegment(row, cols);
    thresholdColumn(&colummSegment);
    groupColumnSegment(&colummSegment);
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
