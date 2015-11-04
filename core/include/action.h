#pragma once
#include <memory>
#include <string>

#include "basic.h"
#include "unit.h"
#include "tile.h"
#include "influence.h"
#include "action_fwd.h"

enum class ActionType {
    Move,
    Atack,
    Pick,
    Interact,
    Destroyed,
};

class Action : public Object {
public:
    Action(ObjectPtr _actor, ObjectPtr _reactor) : actor(_actor), reactor(_reactor) {}
    virtual ObjectPtr get_actor() { return actor; }
    virtual ObjectPtr get_reactor() { return reactor; }
    virtual ActionType get_type() = 0;
    
    static ActionPtr to_ActionPtr(ObjectPtr obj) {
        return std::dynamic_pointer_cast<Action>(obj);
    }

private:
    ObjectPtr actor;
    ObjectPtr reactor;
};

class Move : public Action {
public:
    Move(UnitPtr who, TilePtr where) : Action(who, where) {};
    ActionType get_type() { return ActionType::Move; }
    static MovePtr to_MovePtr(ObjectPtr obj) {
        return std::dynamic_pointer_cast<Move>(obj);
    }
};

class Atack : public Action {
public:
    Atack(ActableObjPtr who, ActableObjPtr whom, Damage _damage) 
        : Action(who, whom), damage(_damage) {}
    ActionType get_type() { return ActionType::Atack; }
    Damage get_damage() { return damage; }
    static AtackPtr to_AtackPtr(ObjectPtr obj) {
        return std::dynamic_pointer_cast<Atack>(obj);
    }
private:
    Damage damage;
};

class Pick : public Action {
public:
    Pick(UnitPtr _who, ItemPtr _what) : Action(_who, _what) {}
    ActionType get_type() { return ActionType::Pick; }
    static PickPtr to_PickPtr(ObjectPtr obj) {
        return std::dynamic_pointer_cast<Pick>(obj);
    }
};

class Interact : public Action {
public:
    Interact(UnitPtr who, ActableObjPtr what, ItemPtr with) : Action(who, what), interactor(with) {}
    ActionType get_type() { return ActionType::Interact; }
    virtual ItemPtr get_interactor() { return interactor; }
    static InteractPtr to_InteractPtr(ObjectPtr obj) {
        return std::dynamic_pointer_cast<Interact>(obj);
    }
private:
    ItemPtr interactor;
};

class Destroyed : public Action {
public:
    Destroyed(ActableObjPtr who, ActableObjPtr whom) : Action(who, whom) {}
    ActionType get_type() { return ActionType::Destroyed; }
    static DestroyedPtr to_DestroyedPtr(ObjectPtr obj) {
        return std::dynamic_pointer_cast<Destroyed>(obj);
    }
};


