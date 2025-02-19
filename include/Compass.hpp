#pragma once
#include <cmath>
#define PI std::acos(-1)

class Compass {
public:
    enum class Direction { N, NE, E, SE, S, SW, W, NW };

    static float toRadian(Direction dir);

    static Direction getEstimatedDirection(float rad, int mode = 0);
};