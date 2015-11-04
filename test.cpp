#include <iostream>

#include "core.h"
#include "getLevel.h"
#include "runUI.h"
#include "tile.h"
#include "basic.h"
#include "visitor.h"

class MyVisistor : public Visitor {
public:
    void visitWallTile (WallTile* w) {
        val = '#';
    }
    void visitFloorTile (FloorTile* f) {
        auto imm = f->get_immovables();
        UnitPtr unit = f->get_unit();
        if (unit) {
            visit(unit);
            return;
        }
        if (!imm.empty()) {
            visit(imm[0]);
            return;
        }
        val = '.';
        return;
    }
    void visitDoor (Door* d) {
        val = 'D';
    }
    void visitHero (Hero* h) {
        val = 'H';
    }
    void defaultVisit() {
        val = 'X';
    }
    char get_val() { return val; }

private:
    char val;
};

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
    getMap();
    print_map();
    //runUI();
}
