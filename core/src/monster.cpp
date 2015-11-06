#include "monster.h"

Monster::Monster(const AIPtr _ai, UnitStats _stats, int _fraction) : Unit(_stats), ai(_ai), fraction(_fraction) { }

void Monster::act() {
    ai->act(get_my_ptr());
}

void Monster::react(ActionPtr action) { }

