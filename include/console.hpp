#pragma once

#include "direction.hpp"

class Console {
public:

    Direction read();

private:

    int _getch();
};
