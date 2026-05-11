#include "space.hpp"

#include <iostream>
#include <random>

Space::Space() {
    _init();
}

void Space::drawPoint(const Point p) {
    if (p.x < 0 || p.y < 0 ||
        p.x >= static_cast<int>(width) || p.y >= static_cast<int>(height)) {
        return;
    }

    std::cout << "\033[" << p.y + 1 << ";" << p.x + 1 << "H";

    if (_space[p.y][p.x] == PointType::kBoard) {
        std::cout << "#";
    } else if (_space[p.y][p.x] == PointType::kFood) {
        std::cout << "\033[31m●\033[0m";
    } else if (_space[p.y][p.x] == PointType::kSnake) {
        std::cout << "\033[32m■\033[0m";
    } else {
        std::cout << " ";
    }

    std::cout.flush();
}

void Space::spawnFood() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<int> xDist(1, static_cast<int>(width) - 2);
    static std::uniform_int_distribution<int> yDist(1, static_cast<int>(height) - 2);

    while (true) {
        Point p {xDist(gen), yDist(gen)};

        if (_space[p.y][p.x] == PointType::kEmpty) {
            changePoint(p, PointType::kFood);
            return;
        }
    }
}

Space::PointType Space::pointType(const Point p) const {
    if (p.x < 0 || p.y < 0 ||
        p.x >= static_cast<int>(width) || p.y >= static_cast<int>(height)) {
        return PointType::kBoard;
    }

    return _space[p.y][p.x];
}

auto Space::changePoint(const Point p, const PointType type) -> bool {
    if (p.x < 0 || p.y < 0 ||
        p.x >= static_cast<int>(width) || p.y >= static_cast<int>(height) ||
        _space[p.y][p.x] == PointType::kBoard ||
        (_space[p.y][p.x] == PointType::kSnake && type != PointType::kEmpty)) {
        return false;
    }
    _space[p.y][p.x] = type;
    drawPoint(p);
    return true;
}

size_t Space::size() const {
    return (width - 2) * (height - 2);
}

void Space::_init() {
    for (auto i = 0; i < height; i++) {
        for (auto j = 0; j < width; j++) {
            if (i == 0 || i == height - 1 || j == 0 || j == width - 1) {
                _space[i][j] = PointType::kBoard;
                std::cout << "#";
            }
            else {
                _space[i][j] = PointType::kEmpty;
                std::cout << " ";
            }
        }
        std::cout << "\n";
    }
}
