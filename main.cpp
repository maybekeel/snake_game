#include "space.hpp"
#include "snake.hpp"
#include "console.hpp"

#include <chrono>
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <thread>

int main() {
    std::cout << "\033[2J\033[H";
    std::cout << "\033[?25l";

    Space space;
    Point start {1, 2};
    Snake snake(start);

    space.changePoint(snake.head(), Space::PointType::kSnake);
    space.spawnFood();

    std::mutex m;
    std::condition_variable cv;
    Direction direction = Direction::kRight;
    bool directionChanged = false;

    std::thread readThread([&] {
        Console console;
        while (true) {
            auto newDirection = console.read();

            {
                std::lock_guard lock(m);
                direction = newDirection;
                directionChanged = true;
            }

            cv.notify_one();
        }
    });
    readThread.detach();

    while (true) {
        {
            std::unique_lock lock(m);
            cv.wait_for(lock, std::chrono::milliseconds(150), [&] {
                return directionChanged;
            });

            if (directionChanged) {
                snake.setDirection(direction);
                directionChanged = false;
            }
        }

        auto oldTail = snake.tail();
        auto nextHead = snake.nextHead();
        bool hasFood = space.pointType(nextHead) == Space::PointType::kFood;

        snake.move(hasFood);

        if (!space.changePoint(snake.head(), Space::PointType::kSnake)) {
            break;
        }

        if (hasFood) {
            space.spawnFood();
        } else {
            space.changePoint(oldTail, Space::PointType::kEmpty);
        }
    }


    std::cout << "\033[?25h";
    std::cout << "\nGame over\n";

    return 0;
}
