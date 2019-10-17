//
// Created by thijs on 17-10-19.
//

#include "ImageProcessor.h"
#include <iostream>


bool ImageProcessor::startVideo(cv::String &filename) {
    cv::VideoCapture _capture(filename);
    capture = _capture;

    if (!capture.isOpened()) {
        std::cerr << "Error opening video stream or file" << std::endl;
        return false;
    }

    capture >> *image;
    return true;
}

void ImageProcessor::closeVideo() {
    capture.release();
    cv::destroyAllWindows();
}

bool ImageProcessor::getNextFrame() {
    capture >> *image;
    return !image->empty();
}

bool ImageProcessor::showImage() {
    if (!initShowImage) {
        cv::namedWindow("Display window", cv::WINDOW_NORMAL); // Create a window for display.
        cv::resizeWindow("Display window", 1366, 768);
    }
    cv::imshow("Display window", *image);
    return cv::waitKey(1) != 27;
}

void* ImageProcessor::segmentationThread(void* arg) {
    // Get Thread Arguments
    ThreadArgs threadArgs = *(ThreadArgs*) arg;
    int &startRow = threadArgs.startRow;
    int &endRow = threadArgs.endRow;
    int &skip = threadArgs.skip;
    Segmentation* segmentation = threadArgs.segmentation;

    for (int row = startRow; row < endRow; row += (1 + skip)) {
        segmentation->getRow(row).col = {}; // segment image
    }
}

Segmentation ImageProcessor::segmentImage() {
    int rows = image->rows;
    Segmentation segmentation = Segmentation(rows);

    // Init Thread arguments
    ThreadArgs targ[nThreads];
    pthread_t tid[nThreads];

    for (int n = 0; n < nThreads; n++) {
        targ[n].startRow = n * rows / nThreads;
        targ[n].endRow = (n + 1) * rows / nThreads;
        targ[n].segmentation = &segmentation;
        targ[n].skip = skip;

        if (pthread_create(&(tid[n]), NULL, &ImageProcessor::segmentationThread, &targ[n]) != 0) {
            printf("Can't create thread %d\n", n);
            return Segmentation(0);
        }
    }

    for (int i = 0; i < nThreads; i++) {
        if (pthread_join(tid[i], NULL) != 0) {
            printf("Can't join thread %d\n", i);
        }
    }

    return segmentation;
}

