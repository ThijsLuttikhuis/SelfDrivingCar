//
// Created by thijs on 31-10-19.
//

#include "image_processing.h"

bool image_processing::setup() {

    // Start Timer
    totalTime = Timer("Total time");
    totalTime.start();

    // Set Debug
    Drawer::setDebug(DEBUG);
    Drawer::setShowOriginalImage(SHOW_ORIGINAL_IMAGE);

    Filters filters;
    filters.minLineLength = MIN_LINE_LENGTH;
    filters.maxLineDistToHorizon = MAX_LINE_D2H;
    filters.minDistToHorizon = MIN_LINE_SEGMENT_D2H;
    filters.horizon = HORIZON;
    filters.verticalLineMaxDistToHorizon = V_LINE_MAX_D2H;
    filters.thresholdColDistance = THRESHOLD_COL_D;
    filters.thresholdMinimumDelta = LINES_ARE_DARK ? -THRESHOLD_MINIMUM_DELTA : THRESHOLD_MINIMUM_DELTA;
    filters.minLineDistToOtherLine = MIN_LINE_D2L;
    filters.minRoadLinePoints = MIN_ROAD_LINE_POINTS;
    filters.minDistanceForSeperateLines = MIN_DF_SEPARATE_LINES;
    filters.printCurrentHorizon = PRINT_HORIZON;
    filters.maxLineGradientDifference = MAX_LINE_GRADIENT_DIFF;
    imageProcessor.setFilters(filters);

    // Get Video
    cv::String filename = FILENAME;
    if (USE_WEBCAM) {
        if (!Drawer::startWebcam()) {
            return false;
        }
        std::cout << "Webcam loaded" << std::endl;
    }
    else {
        if (!Drawer::startVideo(filename)) {
            return false;
        }
        std::cout << "Video loaded" << std::endl;
    }

    // Update Image
    if (!Drawer::getNextFrame(image)) {
        return false;
    }
    std::cout << "image: " << image.rows << "x" << image.cols << std::endl;

    // Start Timer
#if PRINT_TIMING == 1
    // Timing
    timer = Timer("Processing time");
    imshowTime = Timer("Imshow time");
    timer.start();
    imshowTime.start();
#endif
#if PRINT_FPS == 1
    fps = Timer("Frames");
    fps.start();
#endif

    return true;
}

bool image_processing::loop(CarPosition* carPosition) {
    Drawer::clearCopy(image);

    // Segment image
    Segmentation segmentation = imageProcessor.segmentImage(carPosition, SHOW_SEGMENTATION);

    // Combine lines and filter them
    std::vector<Line> lines = imageProcessor.findLines(&segmentation, carPosition, SHOW_LINES);

    // Get actual position of lines
    std::vector<RoadLine> roadLines = imageProcessor.getLinePositions(&lines, carPosition);

    // Get the position of the car on the road.
    imageProcessor.getCarPosition(&roadLines, carPosition, SHOW_ROAD_LINES);

#if PRINT_LINES_FOUND == 1
    std::cout << lines.size() << " lines found, of which " << roadLines.size() << " actual roadlines!" << std::endl;
#endif
#if PRINT_TIMING == 1
    // Timing
    timer.printMilliSeconds();
    imshowTime.start();
#endif

    // Show image
    if (!Drawer::showImage(image, FRAME_BY_FRAME)) {
        return false;
    }

    // Update Image
    if (!Drawer::getNextFrame(image)) {
        return false;
    }

    // Timing
#if PRINT_TIMING == 1
    imshowTime.printMilliSeconds();
    timer.start();
#endif
#if PRINT_FPS == 1
    fps.printFPS();
#endif

    return true;
}

void image_processing::close() {
    // Properly close windows
    Drawer::closeVideo();
    totalTime.printSeconds();
}