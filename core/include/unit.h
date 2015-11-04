#pragma once
#include <memory>

#include "basic.h"
#include "action_fwd.h"
#include "stats.h"

class Unit;
typedef std::shared_ptr<Unit> UnitPtr;

class Unit : public ActableObject {
public:
    Unit(UnitStats _stats) : stats(_stats) {}
    static UnitPtr to_UnitPtr(ObjectPtr obj) {
        return std::dynamic_pointer_cast<Unit>(obj);
    }
private:
    UnitStats stats;
};


