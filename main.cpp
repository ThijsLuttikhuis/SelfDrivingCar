#include <opencv2/core.hpp>

#include "utilities/Timer.h"
#include "imageProcessing/ImageProcessor.h"

#include "imageProcessing/Segmentation.h"
#include "dataStructures/ColumnSegment.h"
#include "utilities/Drawer.h"
#include "dataStructures/RowCol.h"
#include "imageProcessing/RoadLine.h"
#include <iostream>
#include "dataStructures/Filters.h"

// Number of Threads
#define N_THREADS 4

// Line Filters
#define MIN_LINE_LENGTH 8
#define MAX_LINE_D2H 80
#define MIN_LINE_SEGMENT_D2H 200

//#define HORIZON RowCol(410, 500) // compilation720
#define HORIZON RowCol(174, 270) // straight_long
//#define HORIZON RowCol(210, 210) // night
//#define HORIZON RowCol(155, 310) // Lenovo WebCam


// Edge detection threshold parameters
#define LINES_ARE_DARK 0
#define THRESHOLD_COL_DISTANCE 15
#define THRESHOLD_MINIMUM_DELTA 25

// Use webcam or video
#define USE_WEBCAM 0

// Debug mode
#define DEBUG 1
#define SHOW_SEGMENTATION 1
#define SHOW_LINES 1
#define FRAME_BY_FRAME 1
#define SHOW_ORIGINAL_IMAGE 2

int main(int argc, char** argv) {

    // Start Timer
    Timer totalTime("Total time");
    totalTime.start();

    // Set Debug
    Drawer::setDebug(DEBUG);
    Drawer::setShowOriginalImage(SHOW_ORIGINAL_IMAGE);

    // Init image
    cv::Mat image;
    ImageProcessor imageProcessor = ImageProcessor(N_THREADS, image);

    Filters filters;
    filters.minLineLength = MIN_LINE_LENGTH;
    filters.maxLineDistToHorizon = MAX_LINE_D2H;
    filters.minDistToHorizon = MIN_LINE_SEGMENT_D2H;
    filters.horizon = HORIZON;
    filters.thresholdColDistance = THRESHOLD_COL_DISTANCE;
    filters.thresholdMinimumDelta = LINES_ARE_DARK ? -THRESHOLD_MINIMUM_DELTA : THRESHOLD_MINIMUM_DELTA;
    imageProcessor.setFilters(filters);

    // Get Video
    cv::String filename = "../dc_sl.mp4";
    if (USE_WEBCAM && !Drawer::startWebcam()) {
        return -1;
    }
    else if (!Drawer::startVideo(filename)) {
        return -1;
    }

    // Update Image
    if (!Drawer::getNextFrame(image)) {
        return -1;
    }

    // Timing
    Timer timer = Timer("Processing time");
    Timer imshowTime = Timer("Imshow time");
    timer.start();
    imshowTime.start();

    std::cout << image.rows << "x" << image.cols << std::endl;

    while (true) {
        Drawer::clearCopy(image);

        // Segment image
        Segmentation segmentation = imageProcessor.segmentImage(SHOW_SEGMENTATION);

        // Combine lines and filter them
        std::vector<Line> lines = imageProcessor.findLines(&segmentation, SHOW_LINES);
        std::cout << lines.size() << " lines found!" << std::endl;

        // Get actual position of lines
        std::vector<RoadLine> roadLines = imageProcessor.getLinePositions(&lines);

        bool lineExistsLeft = false;
        bool lineExistsRight = false;
        double closestLineColLeft = -filters.horizon.col;
        double closestLineColRight = filters.horizon.col*3;
        for (auto &roadLine : roadLines) {
            roadLine.drawColumn(image);

            double col = roadLine.lineColAtCar;
            if (col < filters.horizon.col) {
                lineExistsLeft = true;
                if (col > closestLineColLeft) {
                    closestLineColLeft = col;
                }
            }
            else {
                lineExistsRight = true;
                if (col < closestLineColRight) {
                    closestLineColRight = col;
                }
            }
        }
        if (lineExistsLeft && lineExistsRight) {
            double distanceLeft = -closestLineColLeft + filters.horizon.col;
            double distanceRight = closestLineColRight - filters.horizon.col;
            std::cout << "left: " << distanceLeft << "    right: " << distanceRight << std::endl;
            if (distanceLeft < distanceRight) {
                Drawer::drawArrowRight(image);
            }
            else {
                Drawer::drawArrowLeft(image);
            }
        }

        // Timing
        timer.printMilliSeconds();
        imshowTime.start();

        // Show image
        if (!Drawer::showImage(image, FRAME_BY_FRAME)) {
            break;
        }

        // Update Image
        if (!Drawer::getNextFrame(image)) {
            break;
        }

        // Timing
        imshowTime.printMilliSeconds();
        timer.start();
    }
    // Properly close windows
    Drawer::closeVideo();
    totalTime.printSeconds();
    return 0;
}