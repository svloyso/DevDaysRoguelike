#pragma once
#include <map>

#include "stats.h"
#include "utils.h"
#include "monster_fwd.h"

enum class RelationType {
    Friend,
    Enemy,
    Neutral
};

enum class StateType {
    Moving,
    Attacking,
    RunAway
};

class AI {
public:
    AI();

    virtual void act(MonsterPtr monster);
protected:
    bool **get_field_of_view(MonsterPtr monster);
    void cast_light(bool** matrix, int start_pos_x, int start_pos_y,
                        int radius, int row, float start_slope,
                            float end_slope, int xx, int xy, int yx, int yy, int x, int y);

    std::vector<UnitPtr> get_all_enemies(MonsterPtr monster, RelationType **unit_map);
    Coord get_nearest_enemy(Coord pos, std::vector<UnitPtr> units);

    ActionPtr make_move_to_enemy(MonsterPtr monster, Coord pos);
    MovePtr make_move(MonsterPtr monster);
        
    RelationType** get_unit_map(MonsterPtr monster, bool** fov);

    bool is_blocked(int x, int y);
};

class SkeletonAI : public AI {
    void act(MonsterPtr monster);
};

class OrkAI : public AI {
    void act(MonsterPtr monster);
};

typedef std::shared_ptr<AI> AIPtr;


