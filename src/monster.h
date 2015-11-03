#pragma once
#include "unit.h"
#include "tile.h"
#include "core.h"
#include "item.h"

#include <vector>

enum class Fraction {
     Undead,
     Orc
};

enum class AI {
    ZombieAI,
    OrcAI
};

enum class StateType {
    None,
    Attack,
    RunAway
};

struct Charactiristics {
    int health;
    uint strength;

    int aggressive;
    int morale;

    uint lineOfSight;
};

struct State {
    ObjectPtr currentDesire;
    StateType stateType;
};

class Monster : public Unit
{
public:
    Monster(const AI ai, Charactiristics charactiristics, Fraction fraction);

private:
    std::vector<std::pair<ObjectPtr, int>> getAllVisibleObject();
    ObjectPtr getDesire();
    int getImportance(ObjectPtr object, int distance);
    Core* core;

    AI ai;
    Charactiristics charactiristics;
};

