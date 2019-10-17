#include <opencv2/core.hpp>

#include "Timer.h"
#include "ImageProcessor.h"

#include "dataStructures/Segmentation.h"
#include "dataStructures/ColumnSegment.h"
#include "Drawer.h"

// Number of Threads
#define N_THREADS 4

// Skip some pixels (for large images)
#define SKIP_ROW 0
#define SKIP_COL 0

// Minimum delta for threshold
#define THRESHOLD 3

// Debug mode
#define DEBUG true
#define FRAME_BY_FRAME true


int main(int argc, char** argv) {
    // Start Timer
    Timer totalTime("Total time");
    totalTime.start();

    // Set Debug
    if (DEBUG) { Drawer::setDebug(); }

    // Init image
    cv::Mat image;
    ImageProcessor imageProcessor = ImageProcessor(N_THREADS, SKIP_ROW, SKIP_COL, THRESHOLD, image);

    // Get Video
    cv::String filename = "/home/thijs/CLionProjects/SelfDrivingCar/dashcam_night.mp4";
    if (!Drawer::startVideo(filename)) {
        return -1;
    }

    // Timing
    Timer timer = Timer();
    timer.start();

    while (true) {
        // Update Image
        if (!Drawer::getNextFrame(image)) {
            break;
        }

        // Segment image
        Segmentation segmentation = imageProcessor.segmentImage();

        // Show Image
        if (!Drawer::showImage(image, FRAME_BY_FRAME)) {
            break;
        }

        // Timing
        timer.printMilliSeconds();
    }

    // Properly close windows
    Drawer::closeVideo();
    totalTime.printSeconds();
    return 0;
}