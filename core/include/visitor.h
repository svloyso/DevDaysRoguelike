#pragma once
#include <functional>

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
    virtual void visitDie(Die* d)  { defaultVisit(); }
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

class CustomVisitor : public Visitor {
    void visitMove(Move* arg) {customMove(arg);}
    void visitAtack(Atack* arg) {customAtack(arg);}
    void visitPick(Pick* arg) {customPick(arg);}
    void visitInteract(Interact* arg) {customInteract(arg);}
    void visitDie(Die* arg) {customDie(arg);}
    void visitDoor(Door* arg) {customDoor(arg);}
    void visitHero(Hero* arg) {customHero(arg);}
    void visitWeapon(Weapon* arg) {customWeapon(arg);}
    void visitClothes(Clothes* arg) {customClothes(arg);}
    void visitUsable(Usable* arg) {customUsable(arg);}
    void visitMonster(Monster* arg) {customMonster(arg);}
    void visitMisc(Misc* arg) {customMisc(arg);}
    void visitTile(Tile* arg) {customTile(arg);}
    void visitWallTile(WallTile* arg) {customWallTile(arg);}
    void visitFloorTile(FloorTile* arg) {customFloorTile(arg);}
    void visitPotion(Potion* arg) {customPotion(arg);}
    void visitKey(Key* arg) {customKey(arg);}
    
    void set_customMove(std::function<void(Move*)> arg) { customMove = arg; }
    void set_customAtack(std::function<void(Atack*)> arg) { customAtack = arg; }
    void set_customPick(std::function<void(Pick*)> arg) { customPick = arg; }
    void set_customInteract(std::function<void(Interact*)> arg) { customInteract = arg; }
    void set_customDie(std::function<void(Die*)> arg) { customDie = arg; }
    void set_customDoor(std::function<void(Door*)> arg) { customDoor = arg; }
    void set_customHero(std::function<void(Hero*)> arg) { customHero = arg; }
    void set_customWeapon(std::function<void(Weapon*)> arg) { customWeapon = arg; }
    void set_customClothes(std::function<void(Clothes*)> arg) { customClothes = arg; }
    void set_customUsable(std::function<void(Usable*)> arg) { customUsable = arg; }
    void set_customMonster(std::function<void(Monster*)> arg) { customMonster = arg; }
    void set_customMisc(std::function<void(Misc*)> arg) { customMisc = arg; }
    void set_customTile(std::function<void(Tile*)> arg) { customTile = arg; }
    void set_customWallTile(std::function<void(WallTile*)> arg) { customWallTile = arg; }
    void set_customFloorTile(std::function<void(FloorTile*)> arg) { customFloorTile = arg; }
    void set_customPotion(std::function<void(Potion*)> arg) { customPotion = arg; }
    void set_customKey(std::function<void(Key*)> arg) { customKey = arg; }
    
private:
    std::function<void(Move*)> customMove = [](Move*) {};
    std::function<void(Atack*)> customAtack = [](Atack*) {};
    std::function<void(Pick*)> customPick = [](Pick*) {};
    std::function<void(Interact*)> customInteract = [](Interact*) {};
    std::function<void(Die*)> customDie = [](Die*) {};
    std::function<void(Door*)> customDoor = [](Door*) {};
    std::function<void(Hero*)> customHero = [](Hero*) {};
    std::function<void(Weapon*)> customWeapon = [](Weapon*) {};
    std::function<void(Clothes*)> customClothes = [](Clothes*) {};
    std::function<void(Usable*)> customUsable = [](Usable*) {};
    std::function<void(Monster*)> customMonster = [](Monster*) {};
    std::function<void(Misc*)> customMisc = [](Misc*) {};
    std::function<void(Tile*)> customTile = [](Tile*) {};
    std::function<void(WallTile*)> customWallTile = [](WallTile*) {};
    std::function<void(FloorTile*)> customFloorTile = [](FloorTile*) {};
    std::function<void(Potion*)> customPotion = [](Potion*) {};
    std::function<void(Key*)> customKey = [](Key*) {};
    virtual void defaultVisit() {}
};

