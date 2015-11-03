#pragma once
#include <memory>
#include <string>

#include "basic.h"

class Action : public Object {
public:
    Action(ObjectPtr _actor, ObjectPtr _reactor);
    ObjectPtr get_actor();
    ObjectPtr get_reactor();
private:
    ObjectPtr actor;
    ObjectPtr reactor;
};

typedef std::shared_ptr<Action> ActionPtr;

