//
// Created by thijs on 31-10-19.
//

#include "IMAGE_PROCESSING/image_processing.h"

int main(int argc, char** argv) {

    cv::Mat image;
    image_processing imageprocessing = image_processing(image);
    if (!imageprocessing.setup()) {
        return -1;
    }

    while (true) {
        if (!imageprocessing.loop()) {
            break;
        }
    }

    imageprocessing.close();
    return 0;
}
