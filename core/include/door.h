#pragma once
#include <memory>

#include "basic.h"
#include "door_fwd.h"
#include "visitor.h"

enum class DoorState {
    Open,
    Closed
};

class Door : public Immovable {

public:
    Door(ActableStatsPtr _stats = ActableStatsPtr()) : Immovable(_stats), state(DoorState::Closed) {}
    void act() {}
    void react(ActionPtr action) {}
    
    DECLARE_COMMON_METHODS(Door)
    DECLARE_VISIT(Door)
private:
    DoorState state;
};

