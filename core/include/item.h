#pragma once
#include <memory>

#include "basic.h"
#include "influence.h"
#include "item_fwd.h"

class Item : public Object {
public:
    Item(Stats _stats) : stats(_stats) {}
    virtual Stats get_stats() { return stats; }

    DECLARE_TO_PTR(Item)
protected:
    Stats stats;
};

class Weapon : public Item {
public:
    Weapon(WeaponStats _stats) : Item(_stats) {}
    
    void visit(Visitor* v) { v->visitWeapon(this); }
    DECLARE_TO_PTR(Weapon)
};

class Clothes : public Item {
public:
    Clothes(ClothesStats _stats) : Item(_stats) {}
    
    void visit(Visitor* v) { v->visitClothes(this); }
    DECLARE_TO_PTR(Clothes)
};

class Usable : public Item {
public:
    Usable(UsableStats _stats) : Item(_stats) {}
    virtual void use(ObjectPtr obj) {}
    
    void visit(Visitor* v) { v->visitUsable(this); }
    DECLARE_TO_PTR(Usable)
};

class Misc : public Item {

public:
    Misc(MiscStats _stats) : Item(_stats) {}
    
    void visit(Visitor* v) { v->visitMisc(this); }
    DECLARE_TO_PTR(Misc)
};

