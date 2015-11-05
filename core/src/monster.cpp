#include "monster.h"
#include "visitor.h"

class MonsterReactVisitor : public Visitor {
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

private:
    MonsterPtr monster;
};

Monster::Monster(const AIPtr _ai, MonsterStatsPtr _stats) : Unit(_stats), ai(_ai) { }

void Monster::act() {
    //ai->act(get_my_ptr());
}

void Monster::react(ActionPtr action) {
    ai->react(get_my_ptr(), action);
    
    MonsterReactVisitor vis;
    vis.visit(action);
}

