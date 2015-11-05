#pragma once
#include <string>
#include <map>

#include "core.h"
#include "tile.h"
#include "visitor.h"
#include "door.h"

class MyVisitor : public Visitor {
public:
    MyVisitor() { init_map(); }

    void visitWallTile (WallTile* w) {
        Coord pos = w->get_coord();
        int r = pos.y;
        int c = pos.x;

        std::string code = "";
        if ((main_core->get_tile (Coord (r, c-1)))->get_type() == TileType::Wall)
            code += "1";
        else
            code += "0";

        if ((main_core->get_tile (Coord (r-1, c)))->get_type() == TileType::Wall)
            code += "1";
        else
            code += "0";

        if ((main_core->get_tile (Coord (r, c+1)))->get_type() == TileType::Wall)
            code += "1";
        else
            code += "0";

        if ((main_core->get_tile (Coord (r+1, c)))->get_type() == TileType::Wall)
            code += "1";
        else
            code += "0";
        val = codes[code];
        color = 15;
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
        val = " ";
    }
    void visitHero(Hero* h) {
        val = "\u2654";
        color = 31;
    }

    void visitMonster(Monster* m) {
        val = "\u2D65";
        color = 15;
    }

    void visitDoor (Door* d) {
        val = "\u2592";
        color = 14;
    }
    void defaultVisit() {
        val = "\u26C0";
        color = 15;
    }
    std::string get_val() { return val; }
    int get_color() { return color; }
private:
    std::map <std::string, std::string> codes;
    void init_map();
    std::string val;
    int color;
};
