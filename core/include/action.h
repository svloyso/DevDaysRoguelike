#pragma once
#include <memory>
#include <string>

#include "basic.h"
#include "unit.h"
#include "tile.h"
#include "impact.h"
#include "action_fwd.h"
#include "visitor.h"

enum class ActionType {
    Move,
    Atack,
    Pick,
    Interact,
    Die,
};

class Action : public Object {
public:
    virtual ActionType get_type() = 0;
    
    DECLARE_COMMON_METHODS(Action)
};

class Move : public Action {
public:
    Move(UnitPtr who, TilePtr where) : actor(who), tile(where) {};
    ActionType get_type() { return ActionType::Move; }

    UnitPtr get_actor() { return actor; }
    TilePtr get_tile()  { return tile;  }
    
    DECLARE_COMMON_METHODS(Move);
    DECLARE_VISIT(Move)
private:
    UnitPtr actor;
    TilePtr tile;
};

class Atack : public Action {
public:
    Atack(ActableObjPtr who, UnitPtr whom, Impact _impact) 
        : actor(who), reactor(whom), impact(_impact) {}
    ActionType      get_type()      { return ActionType::Atack; }
    Impact          get_impact()    { return impact;            }
    ActableObjPtr   get_actor()     { return actor;             }
    UnitPtr         get_reactor()   { return reactor;           }

    DECLARE_COMMON_METHODS(Atack)
    DECLARE_VISIT(Atack)
private:
    ActableObjPtr actor;
    UnitPtr reactor;
    Impact impact;
};

class Pick : public Action {
public:
    Pick(UnitPtr _who, ItemPtr _what) : actor(_who), item(_what) {}
    
    ActionType  get_type()  { return ActionType::Pick;  }
    UnitPtr     get_actor() { return actor;             }
    ItemPtr     get_item()  { return item;              }

    DECLARE_COMMON_METHODS(Pick)
    DECLARE_VISIT(Pick)
private:
    UnitPtr actor;
    ItemPtr item;
};

class Interact : public Action {
public:
    Interact(UnitPtr who, ActableObjPtr what) : actor(who), reactor(what) {}
    
    ActionType      get_type()          { return ActionType::Interact; }
    UnitPtr         get_actor()         { return actor;         }
    ActableObjPtr   get_reactor()       { return reactor;       }
    
    DECLARE_COMMON_METHODS(Interact)
    DECLARE_VISIT(Interact)
private:
    UnitPtr actor;
    ActableObjPtr reactor;
};

class Die : public Action {
public:
    Die(ActableObjPtr who, ActableObjPtr whom) : actor(who), reactor(whom) {}
    ActionType get_type() { return ActionType::Die; }
    ActableObjPtr get_actor() { return actor; }
    ActableObjPtr get_reactor() { return reactor; }
    DECLARE_COMMON_METHODS(Die)
    DECLARE_VISIT(Die)
private:
    ActableObjPtr actor;
    ActableObjPtr reactor;
};

