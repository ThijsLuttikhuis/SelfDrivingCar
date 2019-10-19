//
// Created by thijs on 17-10-19.
//

#include "ImageProcessor.h"
#include "Drawer.h"

Segmentation ImageProcessor::segmentImage() {
    Segmentation segmentation = Segmentation(image);
    segmentation.segmentImage(nThreads);
    return segmentation;
}


