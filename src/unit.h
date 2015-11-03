#pragma once
#include <memory>

#include "basic.h"
#include "action_fwd.h"

class Unit : public VisibleObject {
public:
    Unit();
};

typedef std::shared_ptr<Unit> UnitPtr;

