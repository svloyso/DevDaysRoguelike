#pragma once
#include <vector>
#include <memory>
#include <functional>
#include <unordered_map>

#include "core_fwd.h"
#include "tile_fwd.h"
#include "action.h"
#include "coord.h"
#include "hero.h"
#include "door.h"

struct MapInfo {
    Coord size;
};

enum class Direction {
    Left,
    Right,
    Up,
    Down
};

class Core {
public:
    Core(MapInfo info, const std::vector< std::vector< TilePtr > >& _map);
    TilePtr get_tile(Coord c);
    void subscribe_map(std::function<void(Coord)> f);
    void subscribe_action(std::function<void(ActionPtr)> f);
    Coord get_hero();
	void set_hero(Coord c);

    Result move_hero(Direction dir);

    void do_action(ActionPtr action);
    ObjectPtr get_object(int id);
    MapInfo get_mapinfo();

    void run_game();
private:
    Result do_move(MovePtr action);
    Result do_atack(AtackPtr action);
    Result do_destroy(DestroyedPtr action);
    Result do_interact(InteractPtr action);
    Result do_pick(PickPtr action);

    void init_tables();
private:
    std::vector< std::vector< TilePtr > > map;
    std::function<void(Coord)> map_updater;
    std::function<void(ActionPtr)> action_updater;
    MapInfo map_info;
    std::unordered_map<int, ObjectPtr>  objects;
    std::unordered_map<TilePtr, Coord> tiles;
    Coord hero;
};


void init_core(MapInfo info, const std::vector< std::vector< TilePtr > >& map);

