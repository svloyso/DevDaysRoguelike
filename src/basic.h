#pragma once
#include <memory>

#include "basic_fwd.h"
#include "coord.h"
#include "action_fwd.h"
#include "tile_fwd.h"

enum class Result {
    Success,
    Failure
};

class Object{
public:
    Object() : id(next_id++) {}
    virtual ~Object();
    int get_id() { return id; }
private:
    int id;
    static int next_id;
};

class ActableObject : public Object {
public:
    ActableObject();
    virtual void act();
    virtual void react(ActionPtr action);
    virtual TilePtr get_pos() { return tile; }
    virtual void set_pos(TilePtr t) { tile = t; }

    static ActableObjPtr to_ActableObjPtr(ObjectPtr obj) {
        return std::dynamic_pointer_cast<ActableObject>(obj);
    }
private:
    TilePtr tile;
};

class Immovable : public ActableObject {
public:    
    Immovable();
    static ImmovablePtr to_ImmovablePtr(ObjectPtr obj) {
        return std::dynamic_pointer_cast<Immovable>(obj);
    }
};

