#include "../include/AI.h"  
#include "vector"
#include <map>
#include <vector>
#include "monster.h"
#include <limits.h>
#include <cstdlib>

using namespace std;

const int dir=8;

static int dx[dir]={1, 1, 0, -1, -1, -1, 0, 1};
static int dy[dir]={0, 1, 1, 1, 0, -1, -1, -1};

static int directions[dir][4] = {
    { 1, 0, 0, 1}, //north-west-west
    { 0, 1, 1, 0}, //north-west
    { 0,-1, 1, 0}, //south-west
    {-1, 0, 0, 1}, //south-west-west
    {-1, 0, 0,-1}, //south-east-east
    { 0,-1,-1, 0}, //south-east
    { 0, 1,-1, 0}, //north-east
    { 1, 0, 0,-1}  //north-east-east
};

bool **AI::get_field_of_view(MonsterPtr monster)
{
    int radius = monster->get_stats()->area_of_sight;
    bool** field_of_view = new bool*[radius * 2 + 1];
    for (int i = 0; i < radius * 2 + 1; i++) {
        field_of_view[i] = new bool[radius * 2 + 1];
    }

    Coord pos = monster->get_pos()->get_coord(); // take monster coords

    //for all directions
    for (int i = 0; i < dir; i++) {
        //from center
        cast_light(field_of_view, radius, radius, radius, 1, 1, 0,
                   directions[i][0], directions[i][1], directions[i][2], directions[i][3],
                    pos.x, pos.y
                );
    }
    return field_of_view;
}

void AI::cast_light(bool **field_of_view, int start_pos_x, int start_pos_y, int radius, int row,
                        float start_slope, float end_slope, int xx, int xy, int yx, int yy, int x, int y)
{
    if (start_slope < end_slope) {
        return;
    }
    float next_start_slope = start_slope;
    for (int distance = row;  distance <= radius; distance++) {
        bool blocked = false;
        for (int dx = -distance, dy = -distance; dx <= 0; dx++) {
            float l_slope = (dx - 0.5) / (dy + 0.5);
            float r_slope = (dx + 0.5) / (dy - 0.5);

            if (start_slope < r_slope) {
                continue;
            } else if (end_slope > l_slope) {
                break;
            }

            int diff_x = dx * xx + dy * xy;
            int diff_y = dx * yx + dy * yy;

            int current_x = start_pos_x + diff_x;
            int current_y = start_pos_y + diff_y;
            int radius2 = radius * radius;
            if ((int)(dx * dx + dy * dy) < radius2) {
                field_of_view[current_x][current_y] = true;
            }

            if (blocked) {
                if (is_blocked(x + diff_x, y + diff_y)) {
                    next_start_slope = r_slope;
                    continue;
                } else {
                    blocked = false;
                    start_slope = next_start_slope;
                }
            } else if (is_blocked(x + diff_x, y + diff_y)) {
                blocked = true; 
                next_start_slope = r_slope;
                cast_light(field_of_view, start_pos_x, start_pos_y, radius, distance + 1, start_slope, l_slope, xx,
                        xy, yx, yy, x, y);
            }
        }
        if (blocked) {
            break;
        }
    }
}



std::vector<UnitPtr> AI::get_all_enemies(MonsterPtr monster, RelationType **unit_map)
{
    int radius = monster->get_stats()->area_of_sight;
    Coord pos = monster->get_pos()->get_coord();
    int fov_size = radius * 2 + 1;

    std::vector<UnitPtr> units{};

    for (int row = 0; row < fov_size; row++) {
        for (int col = 0; col < fov_size; col++) {
            if (unit_map[row][col] == RelationType::Enemy) {
                int x = pos.x + col - radius;
                int y = pos.y + row - radius;
                Coord unit_pos{x, y};
                units.push_back(main_core->get_tile(unit_pos)->get_unit());     
            }
        }
    }
    return units;
}


ActionPtr AI::make_move_to_enemy(MonsterPtr monster, Coord pos)
{
    Coord start_pos = monster->get_pos()->get_coord();

    int best_dir_cost = INT_MAX;
    int best_dir_idx = 0;
    for (int i = 0; i < dir; i++) {
        int new_x = start_pos.x + dx[i];
        int new_y = start_pos.x + dx[i];

        int dir_cost = abs(pos.x - new_x) + abs(pos.y - new_y);
        if (dir_cost < best_dir_cost) {
            best_dir_cost = dir_cost;
            best_dir_idx = i;
        }
    }
    Coord next_pos = Coord{start_pos.x + dx[best_dir_idx], start_pos.y + dy[best_dir_idx]};

    if (best_dir_cost == 0) { //means enemy very close
        return std::make_shared<Move>(monster, main_core->get_tile(next_pos));
    }

    return std::make_shared<Move>(monster, main_core->get_tile(next_pos));
}

MovePtr AI::make_move(MonsterPtr monster)
{
    Coord pos = monster->get_pos()->get_coord();
    for (int i = 0; i < dir; i++) {
        int new_x = pos.x + dx[i];
        int new_y = pos.x + dx[i];
        if (!is_blocked(new_x, new_y)) {
            return std::make_shared<Move>(monster, main_core->get_tile(Coord{new_x, new_y}));
        }
    }
    return std::make_shared<Move>(monster, main_core->get_tile(Coord{pos.x, pos.y}));
}

RelationType **AI::get_unit_map(MonsterPtr monster, bool **fov)
{
    int radius = monster->get_stats()->area_of_sight;
    int fov_size = radius * 2 + 1;

    RelationType** unit_map = new RelationType*[fov_size];
    for (int i = 0; i < fov_size; i++) {
        unit_map[i] = new RelationType[fov_size];
    }

    Coord pos = monster->get_pos()->get_coord();

    for (int row = 0; row < fov_size; row++) {
        for (int col = 0; col < fov_size; col++) {
           if (fov[row][col]) {
               TilePtr tile = main_core->get_tile(Coord{pos.x + col - radius, pos.y + row - radius});
               if (tile->get_unit()) { //means we see unit
                   if (tile->get_unit()->get_stats()->fraction != monster->get_stats()->fraction) {
                        unit_map[row][col] = RelationType::Enemy;
                   } else {
                        unit_map[row][col] = RelationType::Friend;
                   }
               }
           }
        }
    }
    return unit_map;
}

bool AI::is_blocked(int x, int y)
{
    return main_core->get_tile(Coord{x, y})->free();
}

Coord get_nearest_unit(Coord pos, vector<UnitPtr> units) {
    int min_dist = INT_MAX;
    Coord min_coord{};
    for (auto unit: units) {
        Coord unit_pos = unit->get_pos()->get_coord();
        int dist = abs(pos.x - unit_pos.x) + abs(pos.y - unit_pos.y);
        if (dist < min_dist) {
            min_dist = dist;
            min_coord = unit_pos;
        }
    }
    return min_coord;
}

HeroPtr SkeletonAI::find_hero(MonsterPtr monster) {
    auto stats = monster->get_stats();
    int sight = stats->area_of_sight;

    TilePtr my_pos = monster->get_pos();
    Coord my_coord = my_pos->get_coord();

    for (int x = my_coord.x - sight; x < my_coord.x + sight; ++x) {
        for (int y = my_coord.y - sight; y < my_coord.y + sight; ++y) {
            //TODO!!!!
        }
    }
    return HeroPtr();
}

void SkeletonAI::act(MonsterPtr monster)
{
    TilePtr my_pos = monster->get_pos();
    Coord my_coord = my_pos->get_coord();
    int tries = 5;
    while(tries--) {
        int x_diff = (rand() % 3) - 1;
        int y_diff = (rand() % 3) - 1;

        Coord coord_to = my_coord;
        coord_to.x += x_diff;
        coord_to.y += y_diff;
        TilePtr tile_to = main_core->get_tile(coord_to);
        MovePtr move = Move::make_Ptr(monster, tile_to);
        Result res = main_core->do_action(move);
        if(res == Result::Success) {
            break;
        }
    }

    return;
    
    bool** fov = get_field_of_view(monster);
    RelationType** unit_map = get_unit_map(monster, fov);

    vector<UnitPtr> enemies = get_all_enemies(monster, unit_map);
    if (enemies.size() > 0) {
        Coord enemy_pos = get_nearest_unit(monster->get_pos()->get_coord(), enemies);
        main_core->do_action(make_move_to_enemy(monster, enemy_pos));
    } else {
        main_core->do_action(make_move(monster));
    }

    int radius = monster->get_stats()->area_of_sight;
    int fov_size = radius * 2 + 1;
    for (int i = 0; i < fov_size; i++) {
        delete[] fov[i];
        delete[] unit_map[i];
    }
    delete[] fov;
    delete[] unit_map;
}


void SkeletonAI::react(MonsterPtr m, ActionPtr a) {}

