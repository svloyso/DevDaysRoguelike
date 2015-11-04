#include <string>
#include <iostream>
#include <fstream>
#include <vector>

#include "core.h"
#include "tile.h"

void fill_tiles(std::string filename, std::vector< std::vector< TilePtr > >& tiles) {
    std::ifstream map(filename);
    
    while(!map.eof()) {
        std::string str;
        std::getline(map, str);
        std::vector< TilePtr > row;
        for(size_t i = 0; i < str.size(); ++i) {
            switch(str[i]) {
                case '#':
                    row.push_back(std::make_shared<WallTile>());
                    break;
                default:
                    row.push_back(std::make_shared<FloorTile>());
                    break;
            }
        }
        tiles.push_back(row);
    }
}

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
            if( tile->get_type() == TileType::Floor ) {
                std::cout << '.';
            }
        }
        std::cout << std::endl;
    }
}

int main() {
    std::string filename("map.txt");
    std::vector< std::vector< TilePtr > > tiles;
    fill_tiles(filename, tiles);
    MapInfo info;
    info.size = Coord(tiles.size(), tiles[0].size());
    init_core(info, tiles);
    print_map();
}
