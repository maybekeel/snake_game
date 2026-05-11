#pragma once

#include <cstddef>

#include "point.hpp"

class Space {
public:
    enum class PointType {
        kEmpty,
        kBoard,
        kFood,
        kSnake 
    };

    Space();

    void drawPoint(Point);
    void spawnFood();
    PointType pointType(Point) const;
    auto changePoint(Point, PointType) -> bool;

private:

    static constexpr size_t width = 140;
    static constexpr size_t height = 40;
    PointType _space[height][width];

    void _init();

};
