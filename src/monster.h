#pragma once
#include "unit.h"
#include "tile.h"
#include "core.h"
#include "item.h"
#include "stats.h"
#include "action.h"

#include <vector>

class Monster : public Unit
{
public:
    Monster(const AIPtr ai, MonsterStats stats);
    void act();
    void react(ActionPtr action);
};

