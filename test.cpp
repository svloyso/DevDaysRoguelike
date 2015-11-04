#include <iostream>

#include "core.h"
#include "getLevel.h"
#include "runUI.h"
#include "tile.h"
#include "basic.h"

void print_map() {
    MapInfo info = main_core->get_mapinfo();
    int width = info.size.x;
    int height = info.size.y;

    for(int x = 0; x < width; ++x) {
        for(int y = 0; y < height; ++y) {
            TilePtr tile = main_core->get_tile(Coord(x, y));
            if( tile->get_type() == TileType::Wall ) {
                std::cout << '#';
            } 
            if ( tile->get_type() == TileType::Floor ) {
                if (tile->get_immovables().size()) {
                    std::cout << 'D';
                } else {
                    std::cout << '.';
                }
            }
        }
        std::cout << std::endl;
    }
}


int main() {
    getMap();
    runUI();
}
