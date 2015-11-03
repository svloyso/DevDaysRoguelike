#pragma once

#include <initializer_list>

struct Coord {
public:
    Coord(int _x, int _y);
    Coord(std::initializer_list<int> l);
    int x;
    int y;
};
