#pragma once
#include <memory>

#include "basic.h"
#include "action_fwd.h"

class Unit : public VisibleObject {
public:
    Unit();
    virtual void act();
    virtual void react(ActionPtr action);
};

typedef std::shared_ptr<Unit> UnitPtr;

