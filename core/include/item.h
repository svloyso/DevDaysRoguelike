#pragma once
#include <memory>

#include "basic.h"
#include "influence.h"

class Item : public Object {
public:
    Item(Stats _stats) : stats(_stats) {}
    virtual Stats get_stats() { return stats; }
private:
    Stats stats;
};

/*
class Weapon : public KeepedItem {
public:
    Weapon(double weight, Damage damage);
};

class Clothes : public KeepedItem {
public:
    Clothes(double weight, Defense defense);
};

class Usable : public KeepedItem {
public:
    Usable(double weight);
    virtual void use(Object* obj);
};
*/

typedef std::shared_ptr<Item>       ItemPtr;
/*typedef std::shared_ptr<PlacedItem> PlacedItemPtr;
typedef std::shared_ptr<KeepedItem> KeepedItemPtr;
typedef std::shared_ptr<Weapon>     WeaponPtr;
typedef std::shared_ptr<Clothes>    ClothesPtr;
typedef std::shared_ptr<Usable>     UsablePtr;
*/

