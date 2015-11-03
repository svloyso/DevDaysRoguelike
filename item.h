#pragma once
#include <memory>

#include "basic.h"
#include "inflection.h"

class Item : public VisibleObject {
public:
    Item(double weight);
    bool movable() = 0;
    double get_weight();
};

typedef std::shared_ptr<Item> ItemPtr;

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
    void use(Object* obj);
};

