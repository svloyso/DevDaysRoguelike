#include "core.h"
#include <stdexcept>

CorePtr main_core;

void init_core(MapInfo info) {
    main_core = std::make_shared<Core>(info, std::vector< std::vector< TilePtr > >());
}

Core::Core(MapInfo info, std::vector< std::vector< TilePtr > > _map) :
    map(_map),
    map_info(info)
{
    init_tables();
}

void Core::init_tables() {
    for (size_t i = 0; i < map.size(); ++i) {
        auto& r = map[i];
        for (size_t j = 0; j < r.size(); ++j) {
            auto t = r[j];
            objects[t->get_id()] = t;
            tiles[t] = Coord(i, j);
            auto unit = t->get_unit();
            objects[unit->get_id()] = unit;
            unit->set_pos(t);
            auto immovables = t->get_immovables();
            auto items = t->get_items();
            for (auto imm : immovables) {
                objects[imm->get_id()] = imm;
                imm->set_pos(t);
            }
            for (auto it : items) {
                objects[it->get_id()] = it;
            }
        }
    }
}

HeroPtr Core::get_hero() {
    return hero;
}

TilePtr Core::get_tile(Coord c) {
    return map[c.x][c.y];
}

void Core::subscribe_map(std::function<void(Coord)> f) {
    map_updater = f;
}

void Core::subscribe_action(std::function<void(ActionPtr)> f) {
    action_updater = f;
}

Result Core::do_move(MovePtr action) {
    UnitPtr actor = Unit::to_UnitPtr(action->get_actor());
    TilePtr tile_to = Tile::to_TilePtr(action->get_reactor());
    TilePtr tile_from = actor->get_pos();

    if (!tile_to->free()) {
        return Result::Failure;
    }
    tile_from->move_from();
    tile_to->move_to(actor);
    
    map_updater(tiles[tile_from]);
    map_updater(tiles[tile_to]);
    return Result::Success;
}

Result Core::do_atack(AtackPtr action) {
    ActableObjPtr actor = ActableObject::to_ActableObjPtr(action->get_actor());
    ActableObjPtr reactor = ActableObject::to_ActableObjPtr(action->get_reactor());

    reactor->react(action);
    return Result::Success;
}

Result do_interact(InteractPtr action) {
    UnitPtr actor = Unit::to_UnitPtr(action->get_actor());
    ActableObjPtr reactor = ActableObject::to_ActableObjPtr(action->get_reactor());
    
    reactor->react(action);
    return Result::Success;
}

Result do_pick(PickPtr action) {
    //TODO
    return Result::Success;
}

Result Core::do_destroy(DestroyedPtr action) {
    ActableObjPtr actor = ActableObject::to_ActableObjPtr(action->get_actor());
    ActableObjPtr reactor = ActableObject::to_ActableObjPtr(action->get_reactor());

    reactor->react(action);
    TilePtr place_of_death = actor->get_pos();
    if (place_of_death->get_unit()->get_id() == actor->get_id()) {
        place_of_death->move_from();
    } else {
        place_of_death->del_immovable(actor->get_id());
    }

    objects.erase(actor->get_id());
    map_updater(tiles[place_of_death]);
    return Result::Success;
}

void Core::do_action(ActionPtr action) {
    switch(action->get_type()) {
        case ActionType::Move:
            do_move(Move::to_MovePtr(action));
            break;
        case ActionType::Atack:
            do_atack(Atack::to_AtackPtr(action));
            break;
        case ActionType::Pick:
            do_pick(Pick::to_PickPtr(action));
            break;
        case ActionType::Interact:
            do_interact(Interact::to_InteractPtr(action));
            break;
        case ActionType::Destroyed:
            do_destroy(Destroyed::to_DestroyedPtr(action));
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

MapInfo Core::get_mapinfo() {
    return map_info;
}

