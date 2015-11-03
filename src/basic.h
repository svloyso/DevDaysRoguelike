#pragma once
#include <memory>

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
};

typedef std::shared_ptr<Object> ObjectPtr;
typedef std::shared_ptr<VisibleObject> VisibleObjPtr;

