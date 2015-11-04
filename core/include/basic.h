#pragma once
#include <memory>

#include "basic_fwd.h"
#include "coord.h"
#include "action_fwd.h"
#include "tile_fwd.h"
#include "visitor_fwd.h"

#define DECLARE_TO_PTR(name) \
    static name##Ptr to_##name##Ptr(ObjectPtr obj) {\
        return std::dynamic_pointer_cast<name>(obj);\
    }

enum class Result {
    Success,
    Failure
};

class Object{
public:
    Object() : id(next_id++) {}
    virtual ~Object() {}
    int get_id() { return id; }
    virtual void visit(Visitor* v)=0;
private:
    int id;
    static int next_id;
};

class ActableObject : public Object {
public:
    virtual void act() = 0;
    virtual void react(ActionPtr action) = 0;
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
    DECLARE_TO_PTR(Immovable)
};

