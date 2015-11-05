#pragma once
#include "visitor.h"
#include "action.h"

class UnitReactVisitor : public Visitor {
public:
    void visitAtack(Atack* atack) {
        ActableObjPtr actor = ActableObject::to_Ptr(atack->get_actor());
        ActableObjPtr reactor = ActableObject::to_Ptr(atack->get_reactor());

        ActableStats* react_stats = reactor->get_stats();
        Damage damage = atack->get_damage();
        react_stats->hit_points -= damage.cutting;
        if (react_stats->hit_points < 0) {
            DestroyedPtr die = Destroyed::make_Ptr(reactor, actor);
            main_core->do_action(die);
        }
    }

    void defaultVisit() { }

};


