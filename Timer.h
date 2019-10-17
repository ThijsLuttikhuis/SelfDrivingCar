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

public:
    explicit Timer(const cv::String& name) : name(name), tStart(-1), tEnd(-1) {};

    Timer() : name("noName"), tStart(-1), tEnd(-1) {};

    void start();

    void end();

    void printSeconds();

    void printMilliSeconds();
};


#endif //SELFDRIVINGCAR_TIMER_H
