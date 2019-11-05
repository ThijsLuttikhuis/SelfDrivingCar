//
// Created by thijs on 31-10-19.
//

#ifndef SELFDRIVINGCAR_MAIN_IMAGE_PROCESSING_H
#define SELFDRIVINGCAR_MAIN_IMAGE_PROCESSING_H

#include <opencv2/core.hpp>

#include "utilities/Timer.h"
#include "imageProcessing/ImageProcessor.h"

#include "imageProcessing/Segmentation.h"
#include "dataStructures/ColumnSegment.h"
#include "utilities/Drawer.h"
#include "dataStructures/RowCol.h"
#include "dataStructures/RoadLine.h"
#include <iostream>
#include "dataStructures/Filters.h"
#include "../CarPosition.h"
#include "../node.h"

// Number of Threads
#define N_THREADS               8

// Line Filters
#define MIN_LINE_LENGTH         58
#define MAX_LINE_D2H            50
#define V_LINE_MAX_D2H          60
#define MIN_LINE_SEGMENT_D2H    30
#define MIN_LINE_D2L            10
#define MIN_ROAD_LINE_POINTS    25
#define MIN_DF_SEPARATE_LINES   100
#define MAX_LINE_GRADIENT_DIFF  0.6

//#define HORIZON RowCol(410, 500) // compilation720
//#define HORIZON RowCol(174, 270) // straight_long
//#define HORIZON RowCol(210, 210) // night
#define HORIZON RowCol(300, 320) // Lenovo WebCam

// Edge detection threshold parameters
#define LINES_ARE_DARK          1
#define THRESHOLD_COL_D         15
#define THRESHOLD_MINIMUM_DELTA 25

// Use webcam or video
#define USE_WEBCAM              1
#define FILENAME                "../dc_sl.mp4"

// Debug mode                 value     //  |       0       |       1       |       2       |       3       |
#define DEBUG                   1       //  | show NOTHING  | debug mode    |               |               |
#define SHOW_SEGMENTATION       0       //  | dont show     | segmentation  |               |               |
#define SHOW_LINES              3       //  | dont show     | simple lines  | extend lines  | show wrong too|
#define SHOW_ROAD_LINES         1       //  | dont show     | road position |               |               |
#define FRAME_BY_FRAME          0       //  | dont show     | frame-by-frame|               |               |
#define SHOW_ORIGINAL_IMAGE     2       //  | thresholded   | original      | show both     |               |
// Print in terminal                    //  |---------------|---------------|---------------|---------------|
#define PRINT_TIMING            0       //  |               |               |               |               |
#define PRINT_FPS               1       //  |               |               |               |               |
#define PRINT_HORIZON           0       //  |               |               |               |               |
#define PRINT_LINES_FOUND       1       //  |               |               |               |               |

class image_processing : public node {
private:

    ImageProcessor imageProcessor;

    Timer totalTime;
#if PRINT_TIMING == 1
    Timer timer;
    Timer imshowTime;
#endif
#if PRINT_FPS == 1
    Timer fps;
#endif

public:
    explicit image_processing(cv::Mat &image) : node(image), imageProcessor(ImageProcessor(N_THREADS, image)) {};
    bool setup() override;
    bool loop(CarPosition* &carPosition) override;
    void close() override;
};

#endif //SELFDRIVINGCAR_MAIN_IMAGE_PROCESSING_H
