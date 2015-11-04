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
    //template <class T>
    //T visit(Visitor* v) { return v->visitDoor(); }
private:
    DoorState state;
};

