#include <opencv2/core.hpp>

#include "utilities/Timer.h"
#include "imageProcessing/ImageProcessor.h"

#include "imageProcessing/Segmentation.h"
#include "dataStructures/ColumnSegment.h"
#include "utilities/Drawer.h"
#include "dataStructures/RowCol.h"
#include "imageProcessing/RoadLine.h"
#include <iostream>

// Number of Threads
#define N_THREADS 16

// Line Filters
#define MIN_LINE_LENGTH 8

//#define HORIZON RowCol(410, 500) // compilation720
//#define HORIZON RowCol(174, 280) // straight_long
#define HORIZON RowCol(210, 210) // night

#define MAX_LINE_D2H 30
#define MIN_LINE_SEGMENT_D2H 200

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

        // Combine lines and filter them
        std::vector<Line> lines = imageProcessor.findLines(&segmentation, SHOW_LINES);
        std::cout << lines.size() << " lines found!" << std::endl;

        // Get actual position of lines
        std::vector<RoadLine> roadLines = imageProcessor.getLinePositions(&lines);
        for (auto &roadLine : roadLines) {
            int size = 20;

            auto col = roadLine.lineColAtCar;
            auto row = image.rows - size - 1;
            for (int i = -size; i < size; i++) {
                for (int j = -size; j < size; j++) {
                    uchar color = 100;
                    int _col = col + i;
                    int _row = row + j;

                    if (_col > 0 && _col < image.cols && _row > 0 && _row < image.rows) {
                        Drawer::setPixel(_row, _col, color);
                    }
                }
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