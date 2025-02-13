#pragma once
#include <cmath>
#include <iostream>
#define PI std::acos(-1)

class Compass {
public:
    enum class Direction {
        N,
        NE,
        E,
        SE,
        S,
        SW,
        W,
        NW
    };

    static float toRadian(Direction dir) {
        switch (dir) {
            case Direction::S:
                return PI * 2 / 4;
            case Direction::SW:
                return PI * 3 / 4;
            case Direction::W:
                return PI * 4 / 4;
            case Direction::NW:
                return PI * 5 / 4;
            case Direction::N:
                return PI * 6 / 4;
            case Direction::NE:
                return PI * 7 / 4;
            case Direction::E:
                return PI * 8 / 4;
            case Direction::SE:
                return PI * 1 / 4;
        }
    }

    static Direction getEstimatedDirection(float rad, int mode = 0) {
        if (rad > (PI * 2)) {
            float r = rad / (PI * 2);
            int i = int(r);
            r = r - i;
            std::cout << r << std::endl;
        }
        if (mode) {
            if (rad <= (PI * 1 / 4) && rad >= (PI * 7 / 4)) { return Direction::E; }
            if (rad < (PI * 3 / 4) && rad > (PI * 1 / 4)) { return Direction::S; }
            if (rad <= (PI * 5 / 4) && rad >= (PI * 3 / 4)) { return Direction::W; }
            if (rad < (PI * 7 / 4) && rad > (PI * 5 / 4)) { return Direction::N; }
        } else {
            if (rad < (PI * 1 / 8) && rad > (PI * 15 / 8)) { return Direction::E; }
            if (rad <= (PI * 3 / 8) && rad >= (PI * 1 / 8)) { return Direction::SE; }
            if (rad < (PI * 5 / 8) && rad > (PI * 3 / 8)) { return Direction::S; }
            if (rad <= (PI * 7 / 8) && rad >= (PI * 5 / 8)) { return Direction::SW; }
            if (rad < (PI * 9 / 8) && rad > (PI * 7 / 8)) { return Direction::W; }
            if (rad <= (PI * 11 / 8) && rad >= (PI * 9 / 8)) { return Direction::NW; }
            if (rad < (PI * 13 / 8) && rad > (PI * 11 / 8)) { return Direction::N; }
            if (rad <= (PI * 15 / 8) && rad >= (PI * 13 / 8)) { return Direction::NE; }
        }
        return Direction::S;
    }
};