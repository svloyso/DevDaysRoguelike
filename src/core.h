#pragma once
#include <vector>
#include <memory>
#include <functional>
#include <unordered_map>

#include "tile.h"
#include "action.h"
#include "coord.h"
#include "hero.h"

struct MapInfo {
    Coord size;
};

class Core {
public:
    Core(MapInfo info, std::vector< std::vector< TilePtr > > _map);
    TilePtr get_tile(Coord c);
    void set_tile(Coord c, TilePtr t);
    void subscribe_map(std::function<void(Coord, TilePtr)> f);
    void subscribe_action(std::function<void(ActionPtr)> f);
    HeroPtr get_hero();

    void do_action(ActionPtr action);
    ObjectPtr get_object(int id);
    Coord get_object_coord(int id);
    MapInfo get_mapinfo();

    void run_game();
private:
    void Move(MovePtr action);
    void Atack(AtackPtr action);
    void Interact(InteractPtr action);
    void Pick(PickPtr action);

    void init_tables();
private:
    std::vector< std::vector< TilePtr > > map;
    std::function<void(Coord, TilePtr)> map_updater;
    std::function<void(ActionPtr)> action_updater;
    MapInfo map_info;
    std::unordered_map<int, VisibleObjPtr> objects;
    std::unordered_map<int, TilePtr>   places;
    HeroPtr hero;
};

typedef std::shared_ptr<Core> CorePtr;

extern CorePtr main_core;

void init_core(MapInfo info);

