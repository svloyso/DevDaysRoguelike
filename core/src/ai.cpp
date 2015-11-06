#include "AI.h"
#include <vector>
#include <map>
#include <vector>
#include <algorithm>
#include "monster.h"
#include <limits.h>
#include <cstdlib>
#include "utils.h"
#include "hero.h"


HeroPtr find_hero(MonsterPtr monster) {
    auto stats = monster->get_stats();
    int sight = stats.area_of_sight;

    TilePtr my_pos = monster->get_pos();
    Coord my_coord = my_pos->get_coord();

    for (int x = my_coord.x - sight; x < my_coord.x + sight; ++x) {
        for (int y = my_coord.y - sight; y < my_coord.y + sight; ++y) {
            TilePtr tile = main_core->get_tile(Coord(x, y));
            UnitPtr unit = tile->get_unit();
            if (unit == main_core->get_hero()) {
                return Hero::cast(unit);
            }
        }
    }
    return HeroPtr();
}

bool can_atack(Coord c1, Coord c2) {
    if ( (c1.x - c2.x)*(c1.y - c2.y) != 0 ) {
        return false;
    }
    if ( abs(c1.x - c2.x) > 1 || abs(c1.y - c2.y) > 1)
        return false;
    return true;
}

bool free_place(Coord c) {
    return main_core->get_tile(c)->free();
}

Coord small_path_search(Coord c1, Coord c2) {
    int steps = 10;
    auto dist = [](Coord c, Coord cc) { return abs(c.x - cc.x) + abs(c.y - cc.y); };

    std::vector<Coord> stack;
    std::map<Coord, int> visited;

    stack.push_back(c1);

    std::vector<Coord> childs;
    while(steps-- && stack.size()) {
        childs.clear();
        Coord c = stack.back();
        stack.pop_back();
        if (c == c2) {
            break;
        }
        visited[c] = steps;
        Coord cc = c.move(Direction::Left);
        if (free_place(cc) && visited.find(cc) == visited.end()) {
            childs.push_back(cc);
        }
        cc = c.move(Direction::Right);
        if (free_place(cc) && visited.find(cc) == visited.end()) {
            childs.push_back(cc);
        }
        cc = c.move(Direction::Up);
        if (free_place(cc) && visited.find(cc) == visited.end()) {
            childs.push_back(cc);
        }
        cc = c.move(Direction::Down);
        if (free_place(cc) && visited.find(cc) == visited.end()) {
            childs.push_back(cc);
        }
        std::sort(childs.begin(), childs.end(), [&](Coord c, Coord cc) { return dist(c2, c) > dist(c2, cc); });
        for (auto ch : childs) { stack.push_back(ch); }
    }

    std::pair<Coord, int> min = std::make_pair(c1, 100);
    for(auto v : visited) {
        if (!(v.first == c1) && can_atack(v.first, c1) && min.second > v.second) {
            min = v;
        }
    }
    return min.first;
}



void make_move(MonsterPtr monster) {
    TilePtr my_pos = monster->get_pos();
    Coord my_coord = my_pos->get_coord();
    int tries = 5;
    while(tries--) {
        int dir = rand() % 4;
        int x_diff = dir % 2 == 0 ? 0 : (dir == 1 ? -1 : 1);
        int y_diff = dir % 2 == 1 ? 0 : (dir == 0 ? -1 : 1);

        Coord coord_to = my_coord;
        coord_to.x += x_diff;
        coord_to.y += y_diff;
        TilePtr tile_to = main_core->get_tile(coord_to);
        MovePtr move = Move::New(monster, tile_to);
        Result res = main_core->do_action(move);
        if(res == Result::Success) {
            break;
        }
    }
}

void atack(MonsterPtr monster, UnitPtr enemy) {
    AtackPtr action;
    Impact impact = monster->get_impact();
    action = Atack::New(monster, enemy, impact);
    main_core->do_action(action);
}

void SkeletonAI::act(MonsterPtr monster) {
    HeroPtr hero = find_hero(monster);
    TilePtr tile = monster->get_pos();
    Coord coord  = tile->get_coord();
    if (hero) {
        TilePtr hero_tile = hero->get_pos();
        Coord hero_coord  = hero_tile->get_coord();
        if (can_atack(coord, hero_coord)) {
            atack(monster, hero);
        } else {
            Coord coord_to = small_path_search(coord, hero_coord);
            TilePtr tile_to = main_core->get_tile(coord_to);
            MovePtr move = Move::New(monster, tile_to);
            main_core->do_action(move);
        }
    } else {
        make_move(monster);
    }
}


void SkeletonAI::react(MonsterPtr m, ActionPtr a) {}

