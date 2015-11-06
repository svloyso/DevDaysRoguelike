#pragma once
#include <string>
#include <map>
#include "core.h"
#include "tile.h"
#include "visitor.h"
#include "door.h"
#include "monster.h"

class PaintVisitor : public Visitor {
public:

    void visitWallTile (WallTile* w) {
        WallType type = w->get_walltype();

        switch (type)   {
            case WallType::lu_corner:
             val= "\u250C";
             break;
            case WallType::ru_corner:
             val= "\u2510";
             break;
            case WallType::lb_corner:
             val= "\u2514";
             break;
            case WallType::rb_corner:
             val= "\u2518";
             break;
            case WallType::horizontal:
             val= "\u2500";
             break;
            case WallType::vertical:
             val= "\u2502";
             break;
            case WallType::cross:
             val= "\u253C";
             break;
            case WallType::t_down:
             val= "\u252C";
             break;
            case WallType::t_up:
             val= "\u2534";
             break;
            case WallType::t_right:
             val= "\u251C";
             break;
            case WallType::t_left:
             val= "\u2524";
             break;
            case WallType::filled:
              val= " ";
            break;
            case WallType::single:
             val= "\u25A1";
            break;
        }
        fg = COLOR_BLUE;
        bg = COLOR_BLACK;
    }

    void visitFloorTile (FloorTile* f) {
        bg = COLOR_BLACK;
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
        auto items = f->get_items();
        if (items.size()) {
            for (auto it : items) {
                visit(it);
            }
            return;
        }
        val = ".";
        fg = COLOR_WHITE;
    }

    void visitHero(Hero* h) {
        val = "\u2689";
        fg = COLOR_RED;
    }    

    void visitMonster(Monster* m) {
        int fraction = m->get_fraction();

        switch(fraction) {
            case (0):
                val = "\u03E8";
                break;
            case(1):
                val = "\u0186";
                break;
            default: //case(2):
                val = "\u2D65";
                break;
        };

        fg = 1 + m->get_id() % 7;
        bg = COLOR_BLACK;

    }

    void visitKey (Key* k)
    {
        val = "\u26B7";
        fg = COLOR_YELLOW;
    }
    void visitDoor (Door* d) {
        val = "X";
        fg = COLOR_WHITE;
    }
    void defaultVisit() {
        val = "*";
        fg = COLOR_WHITE;
        bg = COLOR_BLACK;
    }    
    const char* get_val() { return val; }
    int get_fg() { return fg; }
    int get_bg() { return bg; }
private:
    const char* val;
    int fg;
    int bg;
};
