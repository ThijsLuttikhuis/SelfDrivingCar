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
#include "dataStructures/CarPosition.h"

// Number of Threads
#define N_THREADS               4

// Line Filters
#define MIN_LINE_LENGTH         10
#define MAX_LINE_D2H            120
#define MIN_LINE_SEGMENT_D2H    60
#define MIN_LINE_D2L            10

//#define HORIZON RowCol(410, 500) // compilation720
//#define HORIZON RowCol(174, 270) // straight_long
#define HORIZON RowCol(210, 210) // night
//#define HORIZON RowCol(155, 310) // Lenovo WebCam


// Edge detection threshold parameters
#define LINES_ARE_DARK          0
#define THRESHOLD_COL_DISTANCE  15
#define THRESHOLD_MINIMUM_DELTA 25

// Use webcam or video
#define USE_WEBCAM              0

// Debug mode                 value     //  |       0       |       1       |       2       |
#define DEBUG                   1       //  | show NOTHING  | debug mode    |               |
#define SHOW_SEGMENTATION       1       //  | dont show     | segmentation  |               |
#define SHOW_LINES              2       //  | dont show     | simple lines  | extend lines  |
#define SHOW_ROAD_LINES         1       //  | dont show     | road position |               |
#define FRAME_BY_FRAME          0       //  | dont show     | frame-by-frame|               |
#define SHOW_ORIGINAL_IMAGE     2       //  | thresholded   | original      | show both     |

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
    filters.minLineDistToOtherLine = MIN_LINE_D2L;
    imageProcessor.setFilters(filters);

    // Get Video
    cv::String filename = "../dc_n.mp4";
    if (USE_WEBCAM) {
        if (!Drawer::startWebcam()) {
            return -1;
        }
        std::cout << "Webcam loaded" << std::endl;
    }
    else {
        if (!Drawer::startVideo(filename)) {
            return -1;
        }
        std::cout << "Video loaded" << std::endl;
    }

    // Update Image
    if (!Drawer::getNextFrame(image)) {
        return -1;
    }
    std::cout << "image: " << image.rows << "x" << image.cols << std::endl;

    // Timing
    Timer timer = Timer("Processing time");
    Timer imshowTime = Timer("Imshow time");
    timer.start();
    imshowTime.start();

    while (true) {
        Drawer::clearCopy(image);

        // Segment image
        Segmentation segmentation = imageProcessor.segmentImage(SHOW_SEGMENTATION);

        // Combine lines and filter them
        std::vector<Line> lines = imageProcessor.findLines(&segmentation, SHOW_LINES);

        // Get actual position of lines
        std::vector<RoadLine> roadLines = imageProcessor.getLinePositions(&lines);

        CarPosition carPosition = imageProcessor.getCarPosition(&roadLines, SHOW_ROAD_LINES);

        std::cout << lines.size() << " lines found, of which " << roadLines.size() << " actual roadlines!" << std::endl;

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