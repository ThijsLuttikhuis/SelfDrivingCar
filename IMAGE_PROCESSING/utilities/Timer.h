//
// Created by thijs on 17-10-19.
//

#include <opencv2/core.hpp>

#ifndef SELFDRIVINGCAR_TIMER_H
#define SELFDRIVINGCAR_TIMER_H


class Timer {
private:
    cv::String name;
    int64 tStart;
    int64 tEnd;
    int frames;

public:
    explicit Timer(const cv::String& name) : name(name), tStart(-1), tEnd(-1), frames(0) {};

    Timer() : Timer("noName") {};

    void start();

    void end();

    void printSeconds();

    void printMilliSeconds();

    void printFPS();
};


#endif //SELFDRIVINGCAR_TIMER_H
