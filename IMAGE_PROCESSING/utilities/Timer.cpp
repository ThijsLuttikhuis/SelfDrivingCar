//
// Created by thijs on 17-10-19.
//

#include <iostream>
#include "Timer.h"

void Timer::start() {
    tStart = cv::getTickCount();
}

void Timer::end() {
    tEnd = cv::getTickCount();
}

void Timer::printSeconds() {
    if (tStart == -1) {
        std::cerr << "No start time set" << std::endl;
    }
    if (tEnd == -1 || tEnd < tStart) {
        this->end();
    }
    auto t = (double)(tEnd - tStart) / cv::getTickFrequency();

    if (name == "noName") {
        std::cout << "Time taken: " << t << "s " << std::endl;
    }
    else {
        std::cout << name << " taken: " << t << "s " << std::endl;
    }
    tStart = tEnd;
}

void Timer::printMilliSeconds() {
    if (tStart == -1) {
        std::cerr << "No start time set" << std::endl;
    }
    if (tEnd == -1 || tEnd <= tStart) {
        this->end();
    }
    auto t = (double)(tEnd - tStart) / cv::getTickFrequency();

    if (name == "noName") {
        std::cout << "Time taken: " << t * 1000 << "ms " << std::endl;
    }
    else {
        std::cout << name << " taken: " << t * 1000 << "ms " << std::endl;
    }
    tStart = tEnd;
}

