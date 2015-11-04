#pragma once

#include "basic.h"
#include "influence.h"

struct Stats {
    double weight;
};

struct ItemStats : public Stats {
    // EMPTY
};

struct WeaponStats : public ItemStats {
    Damage damage;
};

struct ClothesStats : public ItemStats {
    Defense defense;
};

struct UsableStats : public ItemStats {
    // EMPTY
};

struct MiscStats : public ItemStats {
    // EMPTY
};

struct ActableStats : public Stats {
    double hit_points;
    double defence;
};

struct UnitStats : public ActableStats {
    double strength;
    double agility;
    double intellegence;
};

enum class Fraction {
     Undead,
     Orc
};

struct MonsterStats : public UnitStats {
    double morale;
    double agression;
    double area_of_sight;
    Fraction fraction;
};

struct HeroStats : public UnitStats {
    //TODO
};
