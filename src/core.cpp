#include "core.h"
#include <stdexcept>

CorePtr main_core;

void init_core(MapInfo info) {
    main_core = std::make_shared(info);
}

Core::Core(MapInfo info, std::vector< std::vector< TilePtr > > _map) :
    map(_map),
    map_info(info)
{
    init_tables();
}

void Core::init_tables() {
    for (int i = 0; i < map.size(); ++i) {
        auto& r = map[i];
        for (int j = 0; j < r.size(); ++j) {
            auto t = r[j];
            //TODO
        }
    }
}

HeroPtr get_hero() {
    return hero;
}

TilePtr Core::get_tile(Coord c) {
    return map[c.x][c.y];
}

void Core::set_tile(Coord c, TilePtr t) {
    map[c.x][c.y] = t;
    map_updater(c, t);
}

void Core::subscribe_map(std::function<void(Coord, TilePtr)> f) {
    map_updater = f;
}

void Core::subscribe_action(std::function<void(ActionPtr)> f) {
    action_updater = f;
}

void Core::Move(MovePtr action) {
    
}

void Core::do_action(ActionPtr action) {
    switch(action->get_type()) {
        case ActionType::Move:
            Move(action);
            break;
        case ActionType::Atack:
            Atack(action);
            break;
        case ActionType::Pick:
            Pick(action);
            break;
        case ActionType::Interract:
            Interract(action);
        default:
            throw std::runtime_error("Invalid action type");
    }
}

ObjectPtr Core::get_object(int id) {
    if (objects.find(id) != objects.end()) {
        return objects[id];
    }
    return ObjectPtr();
}


Coord Core::get_object_coord(int id) {
    if (places.find(id) != places.end()) {
        return places[id]->get_coord();
    }
    return {-1, -1};
}

MapInfo Core::get_mapinfo() {
    return map_info;
}

