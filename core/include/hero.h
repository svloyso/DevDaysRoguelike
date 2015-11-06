#pragma once
#include <memory>

#include "unit.h"
#include "hero_fwd.h"
#include "action.h"

class Hero : public Unit {
public:
    Hero(UnitStats _stats) : Unit(_stats) {}
    void act() {}
    void react(ActionPtr action) {}

    std::string get_name() { return "Анатолий Валерианович"; }
    
    DECLARE_COMMON_METHODS(Hero)
    DECLARE_VISIT(Hero)
};

