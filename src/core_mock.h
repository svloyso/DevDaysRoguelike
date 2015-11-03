#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "coord.h"

class CoreMock {

public:
    CoreMock(const std::string& filename) {
        std::ifstream file(filename);
        while(!file.eof()) {
            std::string str;
            std::getline(file, str);
            map.push_back(str);
        }
    }
    char get_tile(Coord c) {
        return map[c.x][c.y];
    }
    Coord get_size() {
        return Coord(map.size(), map[0].size());
    }
    Coord get_hero() {
        return hero;
    }
    void set_hero(Coord hero_) {
        hero = hero_;
    }
private:
    std::vector< std::string > map;
    Coord hero;
};
