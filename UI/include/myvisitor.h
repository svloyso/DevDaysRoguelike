#pragma once
#include <string>
#include <map>
#include "core.h"
#include "tile.h"
#include "visitor.h"
#include "door.h"
#include "monster.h"
#include "concrete_items.h"
class MyVisitor : public Visitor {
public:

    void visitWallTile (WallTile* w) {
        WallType type = w->get_walltype();

        switch (type)   {
            case WallType::lu_corner:
             val= "\u250C";
             //val = "1";
             break;
            case WallType::ru_corner:
             val= "\u2510";
             //val = "2";
             break;
            case WallType::lb_corner:
             val= "\u2514";
             //val = "3";
             break;
            case WallType::rb_corner:
             val= "\u2518";
             //val = "4";
             break;
            case WallType::horizontal:
             val= "\u2500";
             //val = "5";
             break;
            case WallType::vertical:
             val= "\u2502";
             //val = "6";
             break;
            case WallType::cross:
             val= "\u253C";
             //val = "7";
             break;
            case WallType::t_down:
             val= "\u252C";
             //val = "8";
             break;
            case WallType::t_up:
             val= "\u2534";
             //val = "9";
             break;
            case WallType::t_right:
             val= "\u251C";
             //val = "A";
             break;
            case WallType::t_left:
             val= "\u2524";
             //val = "B";
             break;
            case WallType::filled:
              val= " "; //"\u2591";
              //val = "C";
             break;
            case WallType::single:
             val= "X"; // "\u2591";
             //val = "D";
             break;
        }
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
        val = ".";
        color = 15;
    }

    void visitHero(Hero* h) {
        val = "\u2689";
        color = 33;
    }    

    void visitMonster(Monster* m) {
        val = "\u2D65";
        color = 30 + m->get_id() % 6;
        /*std::map<int,int>::iterator it;
        it = mobsColors.find(m->get_id());
        if (it == mobsColors.end())
            mobsColors[m->get_id()] = 30 + rand() % 77;
        color = mobsColors[m->get_id()];*/
    }
	void visitKey (KeyPtr * k)
{
val = "\u26B7";
color = 93;
}
    void visitDoor (Door* d) {
        val = "X"; // "\u2592";
        color = 14;
    }
    void defaultVisit() {
        val = "\u26C0";
        color = 15;
    }
    std::string get_val() { return val; }
    int get_color() { return color; }
private:
    std::string val;
    int color;
};
