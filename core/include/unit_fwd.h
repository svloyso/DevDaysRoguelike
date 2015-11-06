#pragma once
#include <memory>

class Unit;
typedef std::shared_ptr<Unit> UnitPtr;

struct UnitStats {
    UnitStats(int _hit_points = 1, int _strength = 0, int _agility = 0, int _area_of_sight = 5) : hit_points(_hit_points), strength(_strength), agility(_agility), area_of_sight(_area_of_sight), max_hit_points(_hit_points) {}
    int hit_points;
    int strength;
    int agility;
    int area_of_sight;
    int max_hit_points;
};


