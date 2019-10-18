//
// Created by thijs on 17-10-19.
//

#include "ImageProcessor.h"
#include <thread>
#include "Drawer.h"
#include <iostream>

bool ImageProcessor::thresholdPixel(const cv::Vec3b &pixel) {
    bool left = ((pixel[0] > (&pixel)[-1][0] + minimumDelta) &&
                 (pixel[1] > (&pixel)[-1][1] + minimumDelta) &&
                 (pixel[2] > (&pixel)[-1][2] + minimumDelta));
    bool right = ((pixel[0] > (&pixel)[1][0] + minimumDelta) &&
                  (pixel[1] > (&pixel)[1][1] + minimumDelta) &&
                  (pixel[2] > (&pixel)[1][2] + minimumDelta));

    return left && !right ?
           ((pixel[0] > (&pixel)[-2][0] + minimumDelta / 2) &&
            (pixel[1] > (&pixel)[-2][1] + minimumDelta / 2) &&
            (pixel[2] > (&pixel)[-2][2] + minimumDelta / 2)) :
           right && !left ?
           ((pixel[0] > (&pixel)[2][0] + minimumDelta / 2) &&
            (pixel[1] > (&pixel)[2][1] + minimumDelta / 2) &&
            (pixel[2] > (&pixel)[2][2] + minimumDelta / 2)) :
           left && right ?
           ((pixel[0] > (&pixel)[2][0] + minimumDelta / 2) &&
            (pixel[1] > (&pixel)[2][1] + minimumDelta / 2) &&
            (pixel[2] > (&pixel)[2][2] + minimumDelta / 2)) ||
           ((pixel[0] > (&pixel)[-2][0] + minimumDelta / 2) &&
            (pixel[1] > (&pixel)[-2][1] + minimumDelta / 2) &&
            (pixel[2] > (&pixel)[-2][2] + minimumDelta / 2)) :
           false;
}

void ImageProcessor::thresholdColumn(ColumnSegment* columnSegment) {
    int cols = image.cols;
    const int &row = columnSegment->row;

    cv::Vec3b thresholdedColor = cv::Vec3b(255, 255, 127);
    int width = 5;
    for (int col = 0; col < cols - width; col++) {
        cv::Vec3b* pixel[width];
        int sum = 0;
        for (int c = 0; c < width; c++) {
            pixel[c] = &image.at<cv::Vec3b>(row, col);
            if (thresholdPixel(*pixel[c])) {
                sum++;
            }
        }
        if (sum == width) {
            Drawer::setPixel(*pixel[3], thresholdedColor);
            columnSegment->col.at(col) = true;
        }
    }
}

void ImageProcessor::groupColumnSegment(ColumnSegment* columnSegment) {
//    const int &row = columnSegment->row;
//
//    cv::Vec3b color = cv::Vec3b(0, 0, 255);
//    for (int col = 0; col < image.cols-2;) {
//        if (columnSegment->col.at(++col) && columnSegment->col.at(++col) && columnSegment->col.at(++col)) {
//            Drawer::setPixel(image, row, col, color);
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
