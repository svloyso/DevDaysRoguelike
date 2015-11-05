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
    void visit(ObjectPtr obj);
    virtual void visitMove(Move* m)    { defaultVisit(); }
    virtual void visitAtack(Atack* a)  { defaultVisit(); }
    virtual void visitPick(Pick* p)    { defaultVisit(); }
    virtual void visitInteract(Interact* i)    { defaultVisit(); }
    virtual void visitDestroyed(Destroyed* d)  { defaultVisit(); }
    virtual void visitDoor(Door* d)    { defaultVisit(); }
    virtual void visitHero(Hero* h)    { defaultVisit(); }
    virtual void visitWeapon(Weapon* w){ defaultVisit(); }
    virtual void visitClothes(Clothes* c)      { defaultVisit(); }
    virtual void visitUsable(Usable* u)        { defaultVisit(); }
    virtual void visitMonster(Monster* m)      { defaultVisit(); }
    virtual void visitMisc(Misc* m)    { defaultVisit(); }
    virtual void visitTile(Tile* t)    { defaultVisit(); }
    virtual void visitWallTile(WallTile* w)    { defaultVisit(); }
    virtual void visitFloorTile(FloorTile* f)  { defaultVisit(); }
    virtual void visitPotion(Potion* p){ defaultVisit(); }
    virtual void visitKey(Key* k)        { defaultVisit(); }
    
    virtual void defaultVisit()=0;

};


