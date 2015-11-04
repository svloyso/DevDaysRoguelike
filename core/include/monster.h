#pragma once
#include "unit.h"
#include "tile.h"
#include "core.h"
#include "item.h"
#include "stats.h"
#include "action.h"
#include "monster_fwd.h"
#include "visitor.h"
#include "AI.h"

#include <vector>

class Monster : public Unit
{
public:
    Monster(const AIPtr _ai, MonsterStatsPtr _stats);
    void act();
    void react(ActionPtr action);
    MonsterStats* get_stats() { return MonsterStats::to_MonsterStatsPtr(stats)->get(); }   
    DECLARE_COMMON_METHODS(Monster)
protected:
    AIPtr ai;
};

