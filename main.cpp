#include <opencv2/core.hpp>

#include "Timer.h"
#include "ImageProcessor.h"

#include "dataStructures/Segmentation.h"
#include "dataStructures/ColumnSegment.h"
#include "Drawer.h"
#include "dataStructures/RowCol.h"

// Number of Threads
#define N_THREADS 1

// Line Filters
#define MIN_LINE_LENGTH 8
//#define HORIZON RowCol(410, 500) // compilation720
//#define HORIZON RowCol(174, 280) // straight_long
#define HORIZON RowCol(210, 210) // night
#define MAX_LINE_D2H 30
#define MIN_LINE_SEGMENT_D2H 200
#define MIN_RATIO_LINE_SEGMENT_D2H 2

// Debug mode
#define DEBUG 1
#define SHOW_SEGMENTATION 0
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
    imageProcessor.setHorizon(HORIZON, MIN_LINE_SEGMENT_D2H, MAX_LINE_D2H);
    imageProcessor.setMinLineLength(MIN_LINE_LENGTH);

    // Get Video
    cv::String filename = "/home/thijs/CLionProjects/SelfDrivingCar/dashcam_night.mp4";
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

        // Combine lines
        std::vector<Line> lines = imageProcessor.findLines(&segmentation);

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