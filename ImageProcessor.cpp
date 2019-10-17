//
// Created by thijs on 17-10-19.
//

#include "ImageProcessor.h"
#include <thread>
#include "Drawer.h"
#include <iostream>

bool ImageProcessor::thresholdPixel(const cv::Vec3b &pixel) {
    return ((pixel[0] > (&pixel)[-1][0] + minimumDelta) &&
            (pixel[1] > (&pixel)[-1][1] + minimumDelta) &&
            (pixel[2] > (&pixel)[-1][2] + minimumDelta)) ||
           ((pixel[0] > (&pixel)[1][0] + minimumDelta) &&
            (pixel[1] > (&pixel)[1][1] + minimumDelta) &&
            (pixel[2] > (&pixel)[1][2] + minimumDelta));
}

void ImageProcessor::thresholdColumn(int row, std::vector<int>* columnSegment) {
    int cols = image.cols;
    cv::Vec3b thresholdedColor = cv::Vec3b(255,255,127);
    for (int col = 1; col < cols - 1; col += (1 + skipCol)) {
        auto &pixel = image.at<cv::Vec3b>(row, col);
        if (thresholdPixel(pixel)) {
            Drawer::setPixel(pixel, thresholdedColor);
            columnSegment->push_back(col);
        }
    }
}

std::vector<int> ImageProcessor::segmentColumn(int row) {
    std::vector<int> colummSegment = {};
    thresholdColumn(row, &colummSegment);
    //groupColumnSegment(&colummSegment);
    return colummSegment;
}

void* ImageProcessor::segmentationThread(void* arg) {
    // Get Thread Arguments
    ThreadArgs threadArgs = *(ThreadArgs*) arg;
    int &startRow = threadArgs.startRow;
    int &endRow = threadArgs.endRow;
    Segmentation* segmentation = threadArgs.segmentation;

    for (int row = startRow; row < endRow; row += (1 + skipRow)) {

        ColumnSegment columnSegment = ColumnSegment(row);
        columnSegment.col = segmentColumn(row);

        segmentation->setRow(columnSegment); // segment image
    }
}

Segmentation ImageProcessor::segmentImage() {
    int rows = image.rows;
    Segmentation segmentation = Segmentation(rows);

    // Init Thread arguments
    ThreadArgs targ[nThreads];
    std::thread tid[nThreads];

    for (int n = 0; n < nThreads; n++) {
        targ[n].startRow = n * rows / nThreads;
        targ[n].endRow = (n + 1) * rows / nThreads;
        targ[n].segmentation = &segmentation;

        tid[n] = std::thread(&ImageProcessor::segmentationThread, this,  &targ[n]);
    }

    for (int n = 0; n < nThreads; n++) {
        tid[n].join();
    }

    return segmentation;
}
