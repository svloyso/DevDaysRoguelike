#pragma once

#include "basic.h"

struct Stats {
    double hit_points;
    double weight;
    double defense;
};

struct UnitStats : public Stats {
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
