#include "item.h"
#include <utils>

class Potion : public Usable {
public:
    Potion(int _hp) : hp(_hp) {}
    void use(UnitPtr unit) {
        UnitStats* stats = unit->get_stats();
        stats->hit_points += hp;
        stats->hit_points = std::min(stats->hit_points, stats->max_hit_points);
        unit->drop_item(get_id());
    }
    DECLARE_COMMON_METHODS(Potion)
private:
    int hp;
};

class Key : public Misc {
public:
    Key() {}
    DECLARE_COMMON_METHODS(Key)
};

