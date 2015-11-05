#pragma once
#include <memory>
#include <vector>

#include "basic.h"
#include "action_fwd.h"
#include "stats.h"
#include "unit_fwd.h"
#include "item.h"
#include "visitor.h"

class Unit : public ActableObject {
public:
    Unit(UnitStatsPtr _stats, std::vector<ItemPtr> _items = std::vector<ItemPtr>() ) : ActableObject(_stats), items(_items) {}
    virtual UnitStats* get_stats() { return UnitStats::to_Ptr(stats).get(); }

    std::vector<ItemPtr> get_items() { return items; }
    void pick_item(ItemPtr item) { items.push_back(item); }
    ItemPtr drop_item(int item_id)  {
        for(auto it = items.begin(); it != items.end(); ++it) {
            if((*it)->get_id() == item_id) {
                ItemPtr ret = *it;
                items.erase(it);
                return ret;
            }
        }
        return ItemPtr();
    }

    virtual Damage get_damage() {
        Damage damage;
        damage.cutting = get_stats()->strength;
        if (hands) {
            damage.cutting += hands->get_stats()->damage.cutting;
        }
        return damage;
    }

    ClothesPtr get_head() { return head; }
    ClothesPtr get_body() { return body; }
    WeaponPtr get_hands(){ return hands; }
    ClothesPtr get_legs() { return legs; }

    Result dress_head(int item_id) {
        if(head) return Result::Failure;
        head = Clothes::to_Ptr(drop_item(item_id));
        if(head) return Result::Success;
        return Result::Failure;
    }
    
    Result dress_body(int item_id) {
        if(body) return Result::Failure;
        body = Clothes::to_Ptr(drop_item(item_id));
        if(body) return Result::Success;
        return Result::Failure;
    }
    
    Result dress_hands(int item_id) {
        if(hands) return Result::Failure;
        hands = Weapon::to_Ptr(drop_item(item_id));
        if(hands) return Result::Success;
        return Result::Failure;
    }
    
    Result dress_legs(int item_id) {
        if(legs) return Result::Failure;
        legs = Clothes::to_Ptr(drop_item(item_id));
        if(legs) return Result::Success;
        return Result::Failure;
    }

    Result undress_head() {
        if (!head) return Result::Failure;
        items.push_back(head);
        head = ClothesPtr();
        return Result::Success;
    }
    Result undress_body() {
        if (!body) return Result::Failure;
        items.push_back(body);
        body = ClothesPtr();
        return Result::Success;
    }
    
    Result undress_hands() {
        if (!hands) return Result::Failure;
        items.push_back(hands);
        hands = WeaponPtr();
        return Result::Success;
    }
    
    Result undress_legs() {
        if (!legs) return Result::Failure;
        items.push_back(legs);
        legs = ClothesPtr();
        return Result::Success;
    }

    DECLARE_COMMON_METHODS(Unit)

private:
    std::vector<ItemPtr> items;

    ClothesPtr head;
    ClothesPtr body;
    WeaponPtr hands;
    ClothesPtr legs;
};

