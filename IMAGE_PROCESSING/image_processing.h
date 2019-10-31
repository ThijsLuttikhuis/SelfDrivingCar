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
#include "imageProcessing/RoadLine.h"
#include <iostream>
#include "dataStructures/Filters.h"
#include "../CarPosition.h"
#include "../node.h"

// Number of Threads
#define N_THREADS               4

// Line Filters
#define MIN_LINE_LENGTH         10
#define MAX_LINE_D2H            120
#define MIN_LINE_SEGMENT_D2H    60
#define MIN_LINE_D2L            10

//#define HORIZON RowCol(410, 500) // compilation720
#define HORIZON RowCol(174, 270) // straight_long
//#define HORIZON RowCol(210, 210) // night
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
#define FRAME_BY_FRAME          1       //  | dont show     | frame-by-frame|               |
#define SHOW_ORIGINAL_IMAGE     2       //  | thresholded   | original      | show both     |

class image_processing : public node {
private:

    ImageProcessor imageProcessor;

    Timer totalTime;
    Timer timer;
    Timer imshowTime;

public:
    explicit image_processing(cv::Mat &image) : node(image), imageProcessor(ImageProcessor(N_THREADS, image)) {};
    bool setup() override;
    bool loop(CarPosition* carPosition) override;
    void close() override;
};

#endif //SELFDRIVINGCAR_MAIN_IMAGE_PROCESSING_H
