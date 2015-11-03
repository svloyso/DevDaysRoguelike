#pragma once
#include <memory>

#include "basic.h"
#include "action.h"

class Unit : public VisibleObject {
public:
    Unit();
    void act();
    void react(ActionPtr action);
};

typedef std::shared_ptr<Unit> UnitPtr;

