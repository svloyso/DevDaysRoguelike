#pragma once
#include <memory>

#include "basic.h"
#include "action_fwd.h"
#include "stats.h"
#include "unit_fwd.h"
#include "visitor.h"

class Unit : public ActableObject {
public:
    Unit(UnitStats _stats) : stats(_stats) {}
    
    virtual UnitStats get_stats() { return stats; }
    
    void visit(Visitor* v) { v->visitUnit(this); }

    DECLARE_TO_PTR(Unit)
private:
    UnitStats stats;
};


