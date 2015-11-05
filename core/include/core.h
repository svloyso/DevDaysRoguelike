#pragma once
#include <vector>
#include <memory>
#include <functional>
#include <unordered_map>

#include "basic_fwd.h"
#include "core_fwd.h"
#include "tile_fwd.h"
#include "action_fwd.h"
#include "hero_fwd.h"
#include "door_fwd.h"
#include "utils.h"

struct MapInfo {
    Coord size;
    Coord hero_init;
};

class Core {
public:
    Core(MapInfo info, const std::vector< std::vector< TilePtr > >& _map);
    TilePtr get_tile(Coord c);
    void subscribe_map(std::function<void(Coord)> f);
    void subscribe_action(std::function<void(ActionPtr)> f);
    HeroPtr get_hero();
    UnitPtr get_enemy();

    Result move_hero(Direction dir);
    void wait();

    Result do_action(ActionPtr action);
    ObjectPtr get_object(int id);
    MapInfo get_mapinfo();

    Coord get_coord(TilePtr tile);

private:
    Result do_move(MovePtr action);
    Result do_atack(AtackPtr action);
    Result do_destroy(DestroyedPtr action);
    Result do_interact(InteractPtr action);
    Result do_pick(PickPtr action);

    void init_tables();

    void find_hero_pos();
    void create_hero();
    void make_turn();
    void init_tiles();
private:
    std::vector< std::vector< TilePtr > > map;
    std::function<void(Coord)> map_updater;
    std::function<void(ActionPtr)> action_updater;
    MapInfo map_info;
    std::unordered_map<int, ObjectPtr>  objects;
    std::unordered_map<int, ActableObjPtr> actable;
    std::unordered_map<TilePtr, Coord> tiles;
    HeroPtr hero;
    UnitPtr near_enemy;
};


void init_core(MapInfo info, const std::vector< std::vector< TilePtr > >& map);

