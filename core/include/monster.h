#pragma once
#include "unit.h"
#include "tile.h"
#include "core.h"
#include "item.h"
#include "stats.h"
#include "action.h"
#include "monster_fwd.h"
#include "visitor.h"

#include <vector>

class Monster : public Unit
{
public:
    Monster(const AIPtr ai, MonsterStats _stats) : stats(_stats) {/*TODO*/}
    void act() {/*TODO*/}
    void react(ActionPtr action) {/*TODO*/}
    MonsterStats get_stats() { return stats; }
    
    
    void visit(Visitor* v) { v->visitMonster(this); }
private:
    MonsterStats stats;
};

