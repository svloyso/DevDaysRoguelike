#include "item.h"
#include "unit.h"
#include <algorithm>

void Potion::use(UnitPtr unit) {
    UnitStats stats = unit->get_stats();
    stats.hit_points += hp;
    stats.hit_points = std::min(stats.hit_points, stats.max_hit_points);
    unit->drop_item(get_id());
}
 

