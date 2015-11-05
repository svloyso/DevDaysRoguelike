#include "item.h"
#include "visitor.h"
#include "concrete_items_fwd.h"

#include <utility>

class Potion : public Usable {
public:
    Potion(int _hp) : hp(_hp) {}
    void use(UnitPtr unit) {
        UnitStats* stats = unit->get_stats();
        stats->hit_points += hp;
        stats->hit_points = std::min(stats->hit_points, stats->max_hit_points);
        unit->drop_item(get_id());
    }
    ItemType get_type() { return ItemType::Potion; }
    DECLARE_COMMON_METHODS(Potion)
    DECLARE_VISIT(Potion)
private:
    int hp;
};

class Key : public Misc {
public:
    Key() {}
    ItemType get_type() { return ItemType::Key; }
    DECLARE_COMMON_METHODS(Key)
    DECLARE_VISIT(Key)
};

