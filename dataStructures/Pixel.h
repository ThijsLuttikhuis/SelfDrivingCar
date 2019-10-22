//
// Created by thijs on 22-10-19.
//

#ifndef SELFDRIVINGCAR_PIXEL_H
#define SELFDRIVINGCAR_PIXEL_H

enum PIXEL : char {
    // Dont touch the numbers! :)

    BETWEEN_EDGE_GO_LEFT = -3,
    NO_EDGE_GO_LEFT = 2,

    LEFT_EDGE = -1,
    BETWEEN_EDGE = 0,
    RIGHT_EDGE = 1,

    NO_EDGE_GO_RIGHT = -2,
    BETWEEN_EDGE_GO_RIGHT = 3,

    NO_EDGE = 63,
    UNDEFINED = 127
};

#endif //SELFDRIVINGCAR_PIXEL_H