#pragma once
#include "basic.h"
#include "monster_fwd.h"

class AI : public Object {
public:
    AI() {}
    void act(MonsterPtr monster) {}
    void react(MonsterPtr monster, ActionPtr action) {}
    DECLARE_COMMON_METHODS(AI)
}
