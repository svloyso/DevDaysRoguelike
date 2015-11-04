#pragma once

#include "basic.h"
#include "influence.h"
#include "stats_fwd.h"

struct Stats : public Object{
    double weight;
    DECLARE_COMMON_METHODS(Stats)
};

struct ItemStats : public Stats {
    // EMPTY
    DECLARE_COMMON_METHODS(ItemStats)
};

struct WeaponStats : public ItemStats {
    Damage damage;
    DECLARE_COMMON_METHODS(WeaponStats)
};

struct ClothesStats : public ItemStats {
    Defense defense;
    DECLARE_COMMON_METHODS(ClothesStats)
};

struct UsableStats : public ItemStats {
    DECLARE_COMMON_METHODS(UsableStats)
    // EMPTY
};

struct MiscStats : public ItemStats {
    DECLARE_COMMON_METHODS(MiscStats)
    // EMPTY
};


struct ActableStats : public Stats {
    ActableStats(double hp = 0, double def = 0) : hit_points(hp), defence(def) {}
    double hit_points;
    double defence;
    DECLARE_COMMON_METHODS(ActableStats)
};

enum class Fraction {
     Undead,
     Orc,
     Hero
};

struct UnitStats : public ActableStats {
    double strength;
    double agility;
    double intellegence;
    int area_of_sight;
    Fraction fraction;
    DECLARE_COMMON_METHODS(UnitStats)
};

struct MonsterStats : public UnitStats {
    double morale;
    double agression;
    DECLARE_COMMON_METHODS(MonsterStats)
};

struct HeroStats : public UnitStats {
    //TODO
    DECLARE_COMMON_METHODS(HeroStats)
};


