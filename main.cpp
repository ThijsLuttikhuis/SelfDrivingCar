#include <opencv2/core.hpp>

#include "Timer.h"
#include "ImageProcessor.h"

#include "dataStructures/Segmentation.h"
#include "dataStructures/ColumnSegment.h"
#include "Drawer.h"

// Number of Threads
#define N_THREADS 1

// Minimum delta for threshold
#define THRESHOLD 3
#define MAX_GAP 4

// Debug mode
#define DEBUG 0
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
    ImageProcessor imageProcessor = ImageProcessor(N_THREADS, MAX_GAP, image);

    // Get Video
    cv::String filename = "/home/thijs/CLionProjects/SelfDrivingCar/dashcam_straight_long.mp4";
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
        Segmentation segmentation = imageProcessor.segmentImage();

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