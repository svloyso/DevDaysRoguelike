#include "battle_system.h"
#include "impact.h"
#include "unit_fwd.h"

#include <algorithm>
#include <cstdlib>

int BattleSystem::calculate_damage(Impact impact, Avoidance avoid){
    BodyPart bp = impact.body_part;
    Defense def = avoid.get_def(bp);
    Damage dam = impact.damage;
    UnitStats a_stats = impact.stats;
    UnitStats d_stats = avoid.stats;

    double dodge_chance = 0.5 * (a_stats.agility - d_stats.agility) / (a_stats.agility + d_stats.agility) + 0.5;

    if (rand() / RAND_MAX > dodge_chance) {
        return 0;
    }

    return std::max(1.0, 
        (a_stats.strength/120 + a_stats.agility/100) * std::max(0.0, dam.cutting - def.cutting) +
        (a_stats.strength/70) * std::max(0.0, dam.chopping - def.chopping) + 
        (a_stats.strength/150 + a_stats.agility/120) * std::max(0.0, dam.picking - def.picking) +
        (a_stats.strength/50) * std::max(0.0, dam.crushing - def.crushing));
}
