#include <opencv2/core.hpp>

#include "Timer.h"
#include "ImageProcessor.h"

#include "dataStructures/Segmentation.h"
#include "dataStructures/ColumnSegment.h"

// Number of Threads
#define N_THREADS 8

// Skip some pixels (for large images)
#define SKIP_ROW 0

// Debug mode (comment out if you dont use it)
#define DEBUG

int main(int argc, char** argv) {
    Timer totalTime("Total time");
    totalTime.start();

    // Init image
    cv::Mat image;
    ImageProcessor imageProcessor = ImageProcessor(N_THREADS, SKIP_ROW, &image);

    // Get Video
    cv::String filename = "/home/thijs/CLionProjects/SelfDrivingCar/dashcam_straight_long.mp4";
    if (!imageProcessor.startVideo(filename)) {
        return -1;
    }

    // Timing
    Timer timer = Timer();
    timer.start();

    while (true) {
        // Update Image
        if (!imageProcessor.getNextFrame()) {
            break;
        }

        // Segment image
        Segmentation segmentation = imageProcessor.segmentImage();

#ifdef DEBUG
        // Show Image
        if (!imageProcessor.showImage()) {
            break;
        }
#endif

        // Timing
        timer.printMilliSeconds();
    }

    // Properly close windows
    imageProcessor.closeVideo();
    totalTime.printSeconds();
    return 0;
}