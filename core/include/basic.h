#pragma once
#include <memory>
#include <string>

#include "basic_fwd.h"
#include "utils.h"
#include "action_fwd.h"
#include "tile_fwd.h"
#include "visitor.h"
#include "core.h"

#define DECLARE_COMMON_METHODS(name) \
    static name##Ptr cast(ObjectPtr obj) {\
        return std::dynamic_pointer_cast<name>(obj);\
    }\
    template< class... Args >\
    static name##Ptr New(const Args&... args) {\
        return std::make_shared<name>(args...);\
    }\
    name##Ptr get_my_ptr() {\
        return cast(main_core->get_object(get_id()));\
    }
    
#define DECLARE_VISIT(name) void visit(Visitor* v) { v->visit##name(this); }


class Object{
    friend class Core;
public:
    Object() : id(next_id++) {}
    virtual ~Object() {}
    int get_id() { return id; }
    virtual void visit(Visitor* v) {}
    virtual std::string get_name() { return "Unnamed object"; }
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

    static ActableObjPtr cast(ObjectPtr obj) {
        return std::dynamic_pointer_cast<ActableObject>(obj);
    }
private:
    TilePtr tile;
};

class Immovable : public ActableObject {
public:
    DECLARE_COMMON_METHODS(Immovable)
};

