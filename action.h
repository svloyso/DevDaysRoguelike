#pragma once
#include <memory>
#include <string>

#include "basic.h"
#include "unit.h"
#include "tile.h"

enum class ActionType {
    Move,
    Atack,
    Pick
};

class Action : public Object {
public:
    Action(ObjectPtr _actor, ObjectPtr _reactor) : actor(_actor), reactor(_reactor) {}
    ObjectPtr get_actor() { return actor; }
    ObjectPtr get_reactor() { return reactor; }
    ActionType get_type() = 0;
private:
    ObjectPtr actor;
    ObjectPtr reactor;
};

class Move : public Action {
public:
    Move(UnitPtr _who, TilePtr _where);
    ActionType get_type() { return ActionType::Move; }
};

class Atack : public Action {
public:
    Atack(VisibleObjPtr _who, VisibleObjPtr _whom);
    ActionType get_type() { return ActionType::Atack; }
};

class Pick : public Action {
public:
    Pick(UnitPtr _who, KeepedItem _what);
    ActionType get_type() { return ActionType::Pick; }
};

typedef std::shared_ptr<Action> ActionPtr;
typedef std::shared_ptr<Move>   MovePtr;
typedef std::shared_ptr<Atack>  AtackPtr;
typedef std::shared_ptr<Pick>   PickPtr;

