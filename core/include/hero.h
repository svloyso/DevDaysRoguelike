#pragma once
#include <memory>

#include "unit.h"
#include "stats.h"
#include "hero_fwd.h"
#include "unitvisitor.h"
#include "action.h"

class Hero : public Unit {
public:
    Hero(HeroStatsPtr _stats) : Unit(_stats) {}
    void act() {}
    void react(ActionPtr action) { 
        UnitReactVisitor vis;
        vis.visit(action);
    }
    
    HeroStats* get_stats() { return HeroStats::to_Ptr(stats).get(); }

    DECLARE_COMMON_METHODS(Hero)
    DECLARE_VISIT(Hero)
};

