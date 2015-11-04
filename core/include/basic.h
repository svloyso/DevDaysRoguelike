#pragma once
#include <memory>

#include "basic_fwd.h"
#include "utils.h"
#include "action_fwd.h"
#include "tile_fwd.h"
#include "visitor.h"
#include "core.h"
#include "stats_fwd.h"

#define DECLARE_COMMON_METHODS(name) \
    static name##Ptr to_##name##Ptr(ObjectPtr obj) {\
        return std::dynamic_pointer_cast<name>(obj);\
    }\
    template< class... Args >\
    static name##Ptr make_##name##Ptr(const Args&... args) {\
        return std::make_shared<name>(args...);\
    }\
    name##Ptr get_my_ptr() {\
        return to_##name##Ptr(main_core->get_object(get_id()));\
    }
    
#define DECLARE_VISIT(name) void visit(Visitor* v) { v->visit##name(this); }

class Object{
    friend class Core;
public:
    Object() : id(next_id++) {}
    virtual ~Object() {}
    int get_id() { return id; }
    virtual void visit(Visitor* v) {}
private:
    int id;
    static int next_id;
};

class ActableObject : public Object {
public:
    ActableObject(ActableStatsPtr _stats) : stats(_stats) {}
    virtual void act() = 0;
    virtual void react(ActionPtr action) = 0;
    virtual TilePtr get_pos() { return tile; }
    virtual void set_pos(TilePtr t) { tile = t; }
    virtual ActableStats* get_stats() { return stats.get(); }

    static ActableObjPtr to_ActableObjPtr(ObjectPtr obj) {
        return std::dynamic_pointer_cast<ActableObject>(obj);
    }
protected:
    ActableStatsPtr stats;
private:
    TilePtr tile;
};

class Immovable : public ActableObject {
public:
    Immovable(ActableStatsPtr _stats = ActableStatsPtr()) : ActableObject(_stats) {}
    DECLARE_COMMON_METHODS(Immovable)
};

