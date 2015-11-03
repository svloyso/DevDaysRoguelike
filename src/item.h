#pragma once
#include <memory>

#include "basic.h"
#include "inflection.h"

class Item : public VisibleObject {
public:
    Item(double weight);
    virtual bool movable() = 0;
    virtual double get_weight();
};


class PlacedItem : public Item {
public:
    PlacedItem(double weight);
    bool movable() { return false; }
};

class KeepedItem : public Item {
public:
    KeepedItem(double weight);
    bool movable() { return true; }
};

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

typedef std::shared_ptr<Item>       ItemPtr;
typedef std::shared_ptr<PlacedItem> PlacedItemPtr;
typedef std::shared_ptr<KeepedItem> KeepedItemPtr;
typedef std::shared_ptr<Weapon>     WeaponPtr;
typedef std::shared_ptr<Clothes>    ClothesPtr;
typedef std::shared_ptr<Usable>     UsablePtr;

