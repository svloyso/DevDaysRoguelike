#include "core.h"
#include <stdexcept>

Core::Core(MapInfo info) :
    map(std::vector< std::vector< TilePtr > >(info.size.x, std::vector<TilePtr>(info.size.y, TilePtr()))),
    map_info(info)
{
    // EMPTY
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

void Core::do_action(ActionPtr action) {
    switch(action->get_type()) {
        case ActionType::Move:
            //TODO
            break;
        case ActionType::Atack:
            //TODO
            break;
        case ActionType::Pick:
            //TODO
            break;
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

