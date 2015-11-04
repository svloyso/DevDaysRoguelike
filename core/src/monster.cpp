#include "monster.h"

Monster::Monster(const AIPtr _ai, MonsterStatsPtr _stats) : Unit(_stats), ai(_ai) { }

void Monster::act() {
    ai->act(get_my_ptr());
}

void Monster::react(ActionPtr action) {
    ai->react(get_my_ptr(), action);
    // TODO: implement hp reduction
}

