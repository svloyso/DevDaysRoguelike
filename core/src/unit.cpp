#include "unit.h"
#include "utils.h"
#include "item.h"
#include "impact.h"
#include "action.h"

#include <cstdlib>


void Unit::take_damage(int damage, ActableObjPtr from) {
    stats.hit_points -= damage;
    if (stats.hit_points < 0) {
        DiePtr die = Die::New(get_my_ptr(), from);
        main_core->do_action(die);
    }
}

Impact Unit::get_impact() {
    int r = rand() % 3;
    BodyPart bp = (BodyPart)r;
    return Impact(bp, stats, weapon ? weapon->get_damage() : Damage());
}

Avoidance Unit::get_avoidance() {
    return Avoidance(stats, 
            head ? head->get_defense() : Defense(),
            body ? body->get_defense() : Defense(),
            legs ? legs->get_defense() : Defense());
}

void Unit::pick_item(ItemPtr item) { 
    items.push_back(item); 
}

ItemPtr Unit::drop_item(int item_id) {
    for(auto it = items.begin(); it != items.end(); ++it) {
        if((*it)->get_id() == item_id) {
            ItemPtr ret = *it;
            items.erase(it);
            return ret;
        }
    }
    return ItemPtr();
}

ClothesPtr Unit::get_head() { return head; }
ClothesPtr Unit::get_body() { return body; }
WeaponPtr  Unit::get_weapon(){ return weapon; }
ClothesPtr Unit::get_legs() { return legs; }

Result Unit::dress_head(ClothesPtr _head) {
    if(head) return Result::Failure;
    head = _head;
    return Result::Success;
}

Result Unit::dress_body(ClothesPtr _body) {
    if(body) return Result::Failure;
    body = _body;
    return Result::Success;
}

Result Unit::dress_weapon(WeaponPtr _weapon) {
    if(weapon) return Result::Failure;
    weapon = _weapon;
    return Result::Success;
}

Result Unit::dress_legs(ClothesPtr _legs) {
    if(legs) return Result::Failure;
    legs = _legs;
    return Result::Success;
}

Result Unit::undress_head() {
    if (!head) return Result::Failure;
    items.push_back(head);
    head = ClothesPtr();
    return Result::Success;
}
Result Unit::undress_body() {
    if (!body) return Result::Failure;
    items.push_back(body);
    body = ClothesPtr();
    return Result::Success;
}

Result Unit::undress_weapon() {
    if (!weapon) return Result::Failure;
    items.push_back(weapon);
    weapon = WeaponPtr();
    return Result::Success;
}

Result Unit::undress_legs() {
    if (!legs) return Result::Failure;
    items.push_back(legs);
    legs = ClothesPtr();
    return Result::Success;
}

