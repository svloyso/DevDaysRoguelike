#pragma once

#include "visitor_fwd.h"

#include "action_fwd.h"
#include "basic_fwd.h"
#include "core_fwd.h"
#include "door_fwd.h"
#include "item_fwd.h"
#include "monster_fwd.h"
#include "tile_fwd.h"
#include "unit_fwd.h"
#include "hero_fwd.h"

#include "basic.h"


class Visitor {
public:
    void visit(ObjectPtr obj) {
        return obj->visit(this);
    }

    void visitMove(Move* m)    { defaultVisit(); }
    void visitAtack(Atack* a)  { defaultVisit(); }
    void visitPick(Pick* p)    { defaultVisit(); }
    void visitInteract(Interact* i)    { defaultVisit(); }
    void visitDestroyed(Destroyed* d)  { defaultVisit(); }
    void visitDoor(Door* d)    { defaultVisit(); }
    void visitHero(Hero* h)    { defaultVisit(); }
    void visitWeapon(Weapon* w){ defaultVisit(); }
    void visitClothes(Clothes* c)      { defaultVisit(); }
    void visitUsable(Usable* u)        { defaultVisit(); }
    void visitMonster(Monster* m)      { defaultVisit(); }
    void visitMisc(Misc* m)    { defaultVisit(); }
    void visitTile(Tile* t)    { defaultVisit(); }
    void visitWallTile(WallTile* w)    { defaultVisit(); }
    void visitFloorTile(FloorTile* f)  { defaultVisit(); }
    void visitUnit(Unit* u)    { defaultVisit(); }
    
    virtual void defaultVisit()=0;

};

