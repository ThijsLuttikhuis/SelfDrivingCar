//
// Created by thijs on 17-10-19.
//

#include "Segmentation.h"
#include <thread>
#include "../utilities/Drawer.h"
#include "../dataStructures/ThreadArgs.h"

Segmentation::Segmentation(cv::Mat &_image, bool showSegmentation) : image(_image), showSegmentation(showSegmentation) {
    int _rows = image.rows;
    int _cols = image.cols;
    for (int _row = 0; _row < _rows; _row++) {
        ColumnSegment columnSegment = ColumnSegment(_row, _cols);
        this->segmentationRow.emplace_back(columnSegment);
    }
}

bool Segmentation::thresholdPixel(const cv::Vec3b &pixel) {
    bool left = ((pixel[0] > (&pixel)[-xDist][0] + minimumDelta) &&
                 (pixel[1] > (&pixel)[-xDist][1] + minimumDelta) &&
                 (pixel[2] > (&pixel)[-xDist][2] + minimumDelta));
    bool right = ((pixel[0] > (&pixel)[xDist][0] + minimumDelta) &&
                  (pixel[1] > (&pixel)[xDist][1] + minimumDelta) &&
                  (pixel[2] > (&pixel)[xDist][2] + minimumDelta));

    return left && right;
}


void Segmentation::thresholdColumn(ColumnSegment* columnSegment) {
    int cols = image.cols;
    const int &row = columnSegment->row;
    bool prev = false;
    uchar thresholdedColor[4] = {0, 127, 63, 191};
    for (int col = 0; col < cols - 0; col++) {
        auto &pixel = image.at<cv::Vec3b>(row, col);
        if (thresholdPixel(pixel)) {
            if (!prev) {
                if (showSegmentation) {
                    Drawer::setPixel(row, col, thresholdedColor[1]);
                }
                columnSegment->col.at(col) = PIXEL::LEFT_EDGE;
            } else {
                if (showSegmentation) {
                    Drawer::setPixel(row, col, thresholdedColor[2]);
                }
                columnSegment->col.at(col) = PIXEL::BETWEEN_EDGE;
            }
            prev = true;
        } else {
            if (prev) {
                if (showSegmentation) {
                    Drawer::setPixel(row, col, thresholdedColor[3]);
                }
                columnSegment->col.at(col) = PIXEL::RIGHT_EDGE;
            }
            prev = false;
        }
    }
}

void* Segmentation::segmentationThread(void* arg) {
    // Get Thread Arguments
    ThreadArgs threadArgs = *(ThreadArgs*) arg;
    int &startRow = threadArgs.startRow;
    int &endRow = threadArgs.endRow;

    // Segmentation of columns
    for (int row = startRow; row < endRow; row++) {
        ColumnSegment columnSegment = segmentationRow[row];
        thresholdColumn(&columnSegment);
        segmentationRow[row] = columnSegment;
    }
}

void Segmentation::segmentImage(int nThreads) {
    segmentImage(nThreads, 0, image.rows);
}

void Segmentation::segmentImage(int nThreads, int startRow, int endRow) {
    if (nThreads > 1) {
        // Init Thread arguments
        ThreadArgs targ[nThreads];
        std::thread tid[nThreads];

        for (int n = 0; n < nThreads; n++) {
            targ[n].startRow = startRow + n * (endRow-startRow) / nThreads;
            targ[n].endRow = startRow + (n + 1) * (endRow-startRow) / nThreads;

            tid[n] = std::thread(&Segmentation::segmentationThread, this, &targ[n]);
        }

        for (int n = 0; n < nThreads; n++) {
            tid[n].join();
        }

    }
    else {
        ThreadArgs targ{};
        targ.startRow = startRow;
        targ.endRow = endRow;
        segmentationThread(&targ);
    }
}


