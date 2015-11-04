#pragma once
#include <memory>

#include "basic.h"
#include "action_fwd.h"
#include "stats.h"
#include "unit_fwd.h"
#include "visitor.h"

class Unit : public ActableObject {
public:
    Unit(UnitStatsPtr _stats) : ActableObject(_stats) {}
    virtual UnitStats* get_stats() { return UnitStats::to_Ptr(stats).get(); }

    DECLARE_COMMON_METHODS(Unit)
};

