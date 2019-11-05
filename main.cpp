//
// Created by thijs on 31-10-19.
//

#include "IMAGE_PROCESSING/image_processing.h"
#include "CONTROL/control.h"
#include "GPIO/gpio.h"

std::vector<node*> initStack(cv::Mat &image) {
    std::vector<node*> stack {};

    auto* imageprocessing = new image_processing(image);
    auto* pidcontrol = new control(image);
    auto* gpiocontrol = new gpio(image);

    stack.push_back(imageprocessing);
    //stack.push_back(pidcontrol);
    stack.push_back(gpiocontrol);

    return stack;
}

bool setupStack(std::vector<node*>* stack) {
    bool success = true;
    for (auto &n : *stack) {
        success &= n->setup();
    }
    return success;
}

bool loopStack(std::vector<node*>* stack, CarPosition* carPosition) {
    bool success = true;
    for (auto &n : *stack) {
        success &= n->loop(carPosition);
    }
    return success;
}

void closeStack(std::vector<node*>* stack) {
    for (auto &n : *stack) {
        n->close();
    }
}

int main(int argc, char** argv) {
    // init variables
    cv::Mat image;
    CarPosition carPosition;

    // init stack
    std::vector<node*> stack = initStack(image);

    // setup stack
    setupStack(&stack);

    // loop stack
    bool l = true;
    while (l) {
        l = loopStack(&stack, &carPosition);
    }

    // close stack
    closeStack(&stack);

    return 0;
}

