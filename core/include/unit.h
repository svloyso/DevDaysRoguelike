#pragma once
#include <memory>
#include <vector>
#include <string>

#include "basic.h"
#include "action_fwd.h"
#include "unit_fwd.h"
#include "item_fwd.h"
#include "visitor.h"
#include "impact.h"

class Unit : public ActableObject {
public:
    Unit(UnitStats _stats) : stats(_stats) {}
    std::vector<ItemPtr> get_items() { return items; }
    
    UnitStats get_stats() { return stats; }
    void pick_item(ItemPtr);
    ItemPtr drop_item(int item_id);
    
    Impact get_impact();
    Avoidance get_avoidance();
    void take_damage(int damage, ActableObjPtr);

    ClothesPtr get_head();
    ClothesPtr get_body();
    WeaponPtr  get_weapon();
    ClothesPtr get_legs();
    
    Result dress_head(ClothesPtr);
    Result dress_body(ClothesPtr);
    Result dress_weapon(WeaponPtr);
    Result dress_legs(ClothesPtr);

    Result undress_head();
    Result undress_body();
    Result undress_weapon();
    Result undress_legs();

    DECLARE_COMMON_METHODS(Unit)

private:
    UnitStats stats;
    std::vector<ItemPtr> items;

    ClothesPtr head;
    ClothesPtr body;
    WeaponPtr weapon;
    ClothesPtr legs;
};

