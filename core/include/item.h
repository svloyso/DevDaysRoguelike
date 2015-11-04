#pragma once
#include <memory>

#include "basic.h"
#include "influence.h"
#include "item_fwd.h"

class Item : public Object {
public:
    Item(StatsPtr _stats) : stats(_stats) {}
    virtual Stats* get_stats() { return stats.get(); }

    DECLARE_COMMON_METHODS(Item)
protected:
    StatsPtr stats;
};

class Weapon : public Item {
public:
    Weapon(WeaponStatsPtr _stats) : Item(_stats) {}
    
    WeaponStats* get_stats() { return WeaponStats::to_Ptr(stats).get(); }
    DECLARE_VISIT(Weapon)
    DECLARE_COMMON_METHODS(Weapon)
};

class Clothes : public Item {
public:
    Clothes(ClothesStatsPtr _stats) : Item(_stats) {}
    
    ClothesStats* get_stats() { return ClothesStats::to_Ptr(stats).get(); }
    DECLARE_VISIT(Clothes)
    DECLARE_COMMON_METHODS(Clothes)
};

class Usable : public Item {
public:
    Usable(UsableStatsPtr _stats) : Item(_stats) {}
    virtual void use(ObjectPtr obj) {}
    
    UsableStats* get_stats() { return UsableStats::to_Ptr(stats).get(); }
    DECLARE_VISIT(Usable)
    DECLARE_COMMON_METHODS(Usable)
};

class Misc : public Item {
public:
    Misc(MiscStatsPtr _stats) : Item(_stats) {}

    MiscStats* get_stats() { return MiscStats::to_Ptr(stats).get(); }
    DECLARE_VISIT(Misc)
    DECLARE_COMMON_METHODS(Misc)
};

