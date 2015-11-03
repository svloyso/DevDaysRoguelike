#pragma once
#include <memory>

#include "coord.h"
#include "action_fwd.h"

class Object{
public:
    Object() : id(next_id++) {}
    virtual ~Object();
    int get_id() { return id; }
private:
    int id;
    static int next_id;
};

class VisibleObject : public Object {
public:
    VisibleObject();
    virtual void act();
    virtual void react(ActionPtr action);
    virtual Coord get_coord();
};

typedef std::shared_ptr<Object> ObjectPtr;
typedef std::shared_ptr<VisibleObject> VisibleObjPtr;

