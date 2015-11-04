#pragma once
#include <memory>

#include "basic.h"
#include "door_fwd.h"
//#include "visitor.h"

enum class DoorState {
    Open,
    Closed
};

class Door : public Immovable {

public:
    Door() : state(DoorState::Closed) {}
    virtual void act() {}
    virtual void react(ActionPtr action) {}
    //template <class T>
    //T visit(Visitor* v) { return v->visitDoor(); }
private:
    DoorState state;
};

