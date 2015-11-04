#pragma once

#include "basic.h"

struct Stats {
    double weight;
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
