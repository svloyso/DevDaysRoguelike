#pragma once
#include <memory>

#include "basic.h"
#include "influence.h"
#include "item_fwd.h"


enum class ItemType {
    Weapon,
    Clothes,
    Usable,
    Misc,
    Key,
    Potion
};

class Item : public Object {
public:
    Item(StatsPtr _stats = StatsPtr()) : stats(_stats) {}
    virtual Stats* get_stats() { return stats.get(); }
    
    virtual ItemType get_type()=0;

    DECLARE_COMMON_METHODS(Item)
protected:
    StatsPtr stats;
};

class Weapon : public Item {
public:
    Weapon(WeaponStatsPtr _stats = WeaponStatsPtr()) : Item(_stats) {}
    
    ItemType get_type() { return ItemType::Weapon; }
    WeaponStats* get_stats() { return WeaponStats::to_Ptr(stats).get(); }
    DECLARE_VISIT(Weapon)
    DECLARE_COMMON_METHODS(Weapon)
};

class Clothes : public Item {
public:
    Clothes(ClothesStatsPtr _stats = ClothesStatsPtr()) : Item(_stats) {}
    ItemType get_type() { return ItemType::Clothes; }
    ClothesStats* get_stats() { return ClothesStats::to_Ptr(stats).get(); }
    DECLARE_VISIT(Clothes)
    DECLARE_COMMON_METHODS(Clothes)
};

class Usable : public Item {
public:
    Usable() : Item(UsableStatsPtr()) {}
    virtual void use(UnitPtr unit)=0;
    ItemType get_type() { return ItemType::Usable; }
    UsableStats* get_stats() { return UsableStats::to_Ptr(stats).get(); }
    DECLARE_VISIT(Usable)
    DECLARE_COMMON_METHODS(Usable)
};

class Misc : public Item {
public:
    Misc() : Item(MiscStatsPtr()) {}
    ItemType get_type() { return ItemType::Misc; }
    MiscStats* get_stats() { return MiscStats::to_Ptr(stats).get(); }
    DECLARE_VISIT(Misc)
    DECLARE_COMMON_METHODS(Misc)
};

