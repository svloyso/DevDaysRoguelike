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
    Door(int _key_id = -1) : state(DoorState::Closed), key_id(_key_id) {}
    void act() {}
    void react(ActionPtr action) {}

    std::string get_name() { 
        if(state == DoorState::Closed) {
            return "запертая дверь. Чтобы её открыть нужен ключ"; 
        }
        return "обычная деревянная дверь";
    }

    bool is_open() { return state == DoorState::Open; }
    Result Open(int _key_id) {
        
        //if(key_id == _key_id) 
        {
            state = DoorState::Open;
            return Result::Success;
        }
        return Result::Failure;
    }
    void Close(int _key_id) {
        key_id = _key_id;
        state = DoorState::Closed;
    }

    int get_key_id() { return key_id; }
    
    DECLARE_COMMON_METHODS(Door)
    DECLARE_VISIT(Door)
private:
    DoorState state;
    int key_id;
};

