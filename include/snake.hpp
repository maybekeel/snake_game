#pragma once

#include <cstddef>
#include <deque>

#include "point.hpp"
#include "direction.hpp"

class Snake {
public:

    Snake() = delete;
    Snake(Point);

    Point head() const;
    Point tail() const;
    Point nextHead() const;
    void setDirection(Direction);
    void move(bool);
    size_t size() const;

private:

    std::deque<Point> _body;

    Direction _dir;
};
