#pragma once
#include "unit.h"
#include "action_fwd.h"
#include "monster_fwd.h"
#include "visitor.h"
#include "AI.h"

class Monster : public Unit
{
public:
    Monster(const AIPtr _ai, UnitStats _stats, int _fraction);
    void act();
    void react(ActionPtr action);
    int get_fraction(){ return fraction; }
    DECLARE_COMMON_METHODS(Monster)
    DECLARE_VISIT(Monster)
protected:
    AIPtr ai;
    int fraction;
};

