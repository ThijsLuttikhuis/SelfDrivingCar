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
#define N_THREADS 16

// Line Filters
#define MIN_LINE_LENGTH 8

//#define HORIZON RowCol(410, 500) // compilation720
//#define HORIZON RowCol(174, 280) // straight_long
//#define HORIZON RowCol(210, 210) // night
#define HORIZON RowCol(155, 310) // Lenovo WebCam

#define MAX_LINE_D2H 80
#define MIN_LINE_SEGMENT_D2H 200

// Debug mode
#define DEBUG 1
#define SHOW_SEGMENTATION 1
#define SHOW_LINES 1
#define FRAME_BY_FRAME 0
#define SHOW_ORIGINAL_IMAGE 2

// Edge detection threshold parameters
#define LINES_ARE_DARK 1
#define THRESHOLD_COL_DISTANCE 15
#define THRESHOLD_MINIMUM_DELTA 25

// Use webcam or video
#define USE_WEBCAM 1


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
    cv::String filename;
    if (USE_WEBCAM) {
        filename = "WEBCAM";
    }
    else {
        filename = "/home/thijs/CLionProjects/SelfDrivingCar/dashcam_night.mp4";
    }
    if (!Drawer::startVideo(filename)) {
        return -1;
    }

    // Timing
    Timer timer = Timer("Processing time");
    timer.start();

    Timer imshowTime = Timer("Imshow time");
    imshowTime.start();

    while (true) {
        // Update Image
        if (!Drawer::getNextFrame(image)) {
            break;
        }
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
        double closestLineColLeft = filters.horizon.col;
        double closestLineColRight = filters.horizon.col;
        for (auto &roadLine : roadLines) {
            roadLine.drawColumn(image);

            double col = roadLine.lineColAtCar;
            if (col < filters.horizon.col) {
                lineExistsLeft = true;
                if (col < closestLineColLeft) {
                    closestLineColLeft = col;
                }
            }
            else {
                lineExistsRight = true;
                if (col > closestLineColRight) {
                    closestLineColRight = col;
                }
            }
        }
        if (lineExistsLeft && lineExistsRight) {
            if (fabs(closestLineColLeft - filters.horizon.col) > fabs(closestLineColRight - filters.horizon.col)) {
                Drawer::drawArrowLeft(image);
            }
            else {
                Drawer::drawArrowRight(image);
            }
        }



        // Timing
        timer.printMilliSeconds();
        imshowTime.start();

        // Show image
        if (!Drawer::showImage(image, FRAME_BY_FRAME)) {
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