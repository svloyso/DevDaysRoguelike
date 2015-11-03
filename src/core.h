#pragma once
#include <vector>
#include <memory>
#include <functional>
#include <unordered_map>

#include "tile.h"
#include "action.h"
#include "coord.h"

struct MapInfo {
    Coord size;
};

class Core {
public:
    Core(MapInfo info);
    TilePtr get_tile(Coord c);
    void set_tile(Coord c, TilePtr t);
    void subscribe_map(std::function<void(Coord, TilePtr)> f);
    void subscribe_action(std::function<void(ActionPtr)> f);
    void do_action(ActionPtr action);
    ObjectPtr get_object(int id);
    Coord get_object_coord(int id);
    MapInfo get_mapinfo();

    void run_game();
private:
    std::vector< std::vector< TilePtr > > map;
    std::function<void(Coord, TilePtr)> map_updater;
    std::function<void(ActionPtr)> action_updater;
    MapInfo map_info;
    std::unordered_map<int, ObjectPtr> objects;
    std::unordered_map<int, TilePtr>   places;
};
