#include <string>
#include <iostream>
#include <fstream>
#include <vector>

#include "core.h"
#include "tile.h"
#include "visitor.h"
#include "door.h"

class MyVisistor : public Visitor {
public:
    void visitWallTile (WallTile* w) {
        val = '#';
    }
    void visitFloorTile (FloorTile* f) {
        auto imm = f->get_immovables();
        if (imm.empty()) {
            val = '.';
            return;
        }
        visit(imm[0]);
    }
    void visitDoor (Door* d) {
        val = 'D';
    }
    void defaultVisit() {
        val = 'X';
    }
    char get_val() { return val; }

private:
    char val;
};

void fill_tiles(std::string filename, std::vector< std::vector< TilePtr > >& tiles) {
    std::ifstream map(filename);
    
    while(!map.eof()) {
        std::string str;
        std::getline(map, str);
        std::vector< TilePtr > row;
        for(size_t i = 0; i < str.size(); ++i) {
            TilePtr tile;
            std::vector< ImmovablePtr > imms;
            switch(str[i]) {
                case '#':
                    tile = std::make_shared<WallTile>();
                    break;
                case 'D':
                    imms.push_back(std::make_shared<Door>());
                    tile = std::make_shared<FloorTile>(UnitPtr(), std::vector<ItemPtr>(), imms);
                    break;
                default:
                    tile = std::make_shared<FloorTile>();
                    break;
            }
            row.push_back(tile);
        }
        if(row.size()) {
            tiles.push_back(row);
        }
    }
}

void print_map() {
    MapInfo info = main_core->get_mapinfo();
    int width = info.size.x;
    int height = info.size.y;
    MyVisistor visitor;

    for(int x = 0; x < width; ++x) {
        for(int y = 0; y < height; ++y) {
            TilePtr tile = main_core->get_tile(Coord(x, y));
            visitor.visit(tile);
            char c = visitor.get_val();
            std::cout << c;
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
