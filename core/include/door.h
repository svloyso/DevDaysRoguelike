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
    Door() : state(DoorState::Closed) {}
    void act() {}
    void react(ActionPtr action) {}
    
    void visit(Visitor* v) { v->visitDoor(this); }
private:
    DoorState state;
};

