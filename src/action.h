#pragma once
#include <memory>
#include <string>

#include "basic.h"
#include "unit.h"
#include "tile.h"
#include "action_fwd.h"

enum class ActionType {
    Move,
    Atack,
    Pick,
    Interract
};

class Action : public Object {
public:
    Action(ObjectPtr _actor, ObjectPtr _reactor) : actor(_actor), reactor(_reactor) {}
    virtual ObjectPtr get_actor() { return actor; }
    virtual ObjectPtr get_reactor() { return reactor; }
    virtual ActionType get_type() = 0;
private:
    ObjectPtr actor;
    ObjectPtr reactor;
};

class Move : public Action {
public:
    Move(std::shared_ptr<Unit> who, TilePtr where);
    ActionType get_type() { return ActionType::Move; }
};

class Atack : public Action {
public:
    Atack(VisibleObjPtr _who, VisibleObjPtr _whom);
    ActionType get_type() { return ActionType::Atack; }
};

class Pick : public Action {
public:
    Pick(UnitPtr _who, KeepedItemPtr _what);
    ActionType get_type() { return ActionType::Pick; }
};

class Interract : public Action {
public:
    Interract(UnitPtr who, VisibleObjPtr what, KeepedItemPtr with);
    ActionType get_type() { return ActionType::Interract; }
    virtual KeepedItemPtr get_interractor();
};

typedef std::shared_ptr<Move>   MovePtr;
typedef std::shared_ptr<Atack>  AtackPtr;
typedef std::shared_ptr<Pick>   PickPtr;
typedef std::shared_ptr<Interract> InterractPtr;
