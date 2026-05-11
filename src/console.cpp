#include "console.hpp"

#include <termios.h>
#include <unistd.h>
#include <cstdio>

#include "direction.hpp"

Direction Console::read() {
    int ch;
    while ((ch = _getch()) != 'q') {
        if (ch == 27) {
            _getch();
            switch(_getch()) {
                case 'A': return Direction::kUp;
                case 'B': return Direction::kDown;
                case 'C': return Direction::kRight;
                case 'D': return Direction::kLeft;
            }
        }
    }

    return Direction::kRight;
}

int Console::_getch() {
    struct termios oldt, newt;
    int ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}
