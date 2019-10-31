//
// Created by thijs on 31-10-19.
//

#include "IMAGE_PROCESSING/image_processing.h"
#include "CONTROL/control.h"

std::vector<stack*> setupStack(cv::Mat &image) {
    std::vector<stack*> stack {};

    auto* imageprocessing = new image_processing(image);
    auto* pidcontrol = new control(image);

    stack.push_back(imageprocessing);
    stack.push_back(pidcontrol);

    return stack;
}

int main(int argc, char** argv) {

    // init variables
    cv::Mat image;
    CarPosition carPosition;
    bool loop = true;

    // make stack
    std::vector<stack*> stack = setupStack(image);

    // setup stack
    for (auto &n : stack) {
        n->setup();
    }

    // loop stack
    while (loop) {
        for (auto &n : stack) {
            if (!n->loop(&carPosition)) {
                loop = false;
            }
        }
    }

    // close stack
    for (auto &n : stack) {
        n->close();
    }

    return 0;

}
