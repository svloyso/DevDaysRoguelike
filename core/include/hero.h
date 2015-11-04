#pragma once
#include <memory>

#include "unit.h"
#include "stats.h"
#include "hero_fwd.h"
#include "visitor.h"

class Hero : public Unit {
public:
    Hero(HeroStats _stats) : Unit(_stats) {}

    
    void visit(Visitor* v) { v->visitHero(this); }
};

