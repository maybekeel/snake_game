#include "snake.hpp"

Snake::Snake(const Point start) {
    _dir = Direction::kRight;
    _body.push_back(start);
}

Point Snake::head() const {
    return _body.front();
}

Point Snake::tail() const {
    return _body.back();
}

Point Snake::nextHead() const {
    auto next = _body.front();

    if (_dir == Direction::kUp) {
        next.y -= 1;
    } else if (_dir == Direction::kDown) {
        next.y += 1;
    } else if (_dir == Direction::kLeft) {
        next.x -= 1;
    } else {
        next.x += 1;
    }

    return next;
}

void Snake::setDirection(Direction d) {
    if ((_dir == Direction::kUp && d != Direction::kDown) ||
        (_dir == Direction::kDown && d != Direction::kUp) ||
        (_dir == Direction::kLeft && d != Direction::kRight) ||
        (_dir == Direction::kRight && d != Direction::kLeft)) {
        _dir = d;
    }
}

void Snake::move(bool food) {

    _body.push_front(nextHead());

    if (!food) {
        _body.pop_back();
    } 

}

size_t Snake::size() const {
    return _body.size();
}
