#pragma once
#include <memory>

#include "unit.h"
#include "stats.h"

class Hero : public Unit {
public:
    Hero(HeroStats _stats);
private:
    HeroStats stats;
};

typedef std::shared_ptr<Hero> HeroPtr;
