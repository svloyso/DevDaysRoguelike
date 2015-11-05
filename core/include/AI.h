#pragma once
#include "basic.h"
#include "monster_fwd.h"
#include "AI_fwd.h"
#include "monster_fwd.h"

enum class RelationType {
    Friend,
    Enemy,
    Neutral
};

enum class StateType {
    Moving,
    Attacking,
    RunAway
};

class AI : public Object {
public:
    AI() {}
    virtual void act(MonsterPtr monster) {}
    virtual void react(MonsterPtr monster, ActionPtr action) {}
    DECLARE_COMMON_METHODS(AI)

};

class SkeletonAI : public AI {
public:
    void act(MonsterPtr monster);
    void react(MonsterPtr monster, ActionPtr action);
    DECLARE_COMMON_METHODS(SkeletonAI)
};

class OrcAI : public AI {
public:
    void act(MonsterPtr monster);
    void react(MonsterPtr monster, ActionPtr action);
    DECLARE_COMMON_METHODS(OrcAI)
};

