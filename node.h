//
// Created by thijs on 31-10-19.
//

#ifndef SELFDRIVINGCAR_NODE_H
#define SELFDRIVINGCAR_NODE_H


#include <opencv2/core/mat.hpp>
#include "CarPosition.h"

class node {
protected:
    cv::Mat &image;
public:
    explicit node(cv::Mat &image) : image(image) {};
    virtual bool setup() = 0;
    virtual bool loop(CarPosition* &carPosition) = 0;
    virtual void close() = 0;
};


#endif //SELFDRIVINGCAR_NODE_H
