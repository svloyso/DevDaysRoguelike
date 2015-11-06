#include <stdexcept>
#include <memory>
#include <string>
#include <map>

#include "tile.h"
#include "core.h"
#include "hero.h"
#include "action.h"
#include "door.h"

CorePtr main_core;

void init_core(MapInfo info, const std::vector< std::vector< TilePtr > >& map) {
    main_core = std::make_shared<Core>(info, std::ref(map));
}

Core::Core(MapInfo info, const std::vector< std::vector< TilePtr > >& _map) :
    map(_map),
    map_info(info)
{
    init_tables();
    init_tiles();
    create_hero();
    map_updater = [](Coord c) {};
    action_updater = [](ActionPtr a) {};
}

void Core::find_hero_pos() {
    for(int x = 1; x < map_info.size.x; ++x) {
        TilePtr tile(get_tile(Coord(x, x)));
        if (tile->get_type() != TileType::Wall) {
            tile->unit = hero;
            return;
        }
    }
}

void Core::create_hero() {
    UnitStats stats(400, 50, 30); 
    WeaponPtr sword = Weapon::New(10, Damage(20, 5), "Обычный меч");
    ClothesPtr hat = Clothes::New(2, Defense(5, 5, 5, 5, 5), "Шапка-ушанка");
    ClothesPtr shirt = Clothes::New(3, Defense(7, 7, 7, 7, 7), "Потрепанная куртка");
    ClothesPtr pants = Clothes::New(3, Defense(6, 6, 6, 6, 6), "Джинсы");
    
    hero = Hero::New(stats);
    hero->dress_head(hat);
    hero->dress_body(shirt);
    hero->dress_legs(pants);
    hero->dress_weapon(sword);

    objects[hero->get_id()] = hero;
    TilePtr hero_tile = get_tile(map_info.hero_init);
    hero_tile->unit = hero;
    hero->set_pos(hero_tile);
}

void Core::init_tables() {
    std::vector<DoorPtr> doors;
    std::vector<KeyPtr>  keys;
    for (size_t i = 0; i < map.size(); ++i) {
        auto& r = map[i];
        for (size_t j = 0; j < r.size(); ++j) {
            auto t = r[j];
            objects[t->get_id()] = t;
            tiles[t] = Coord(i, j);
            auto unit = t->get_unit();
            if(unit) {
                objects[unit->get_id()] = unit;
                actable[unit->get_id()] = unit;
                unit->set_pos(t);
            }
            auto immovables = t->get_immovables();
            auto items = t->get_items();
            for (auto imm : immovables) {
                objects[imm->get_id()] = imm;
                imm->set_pos(t);
                doors.push_back(Door::cast(imm));
            }
            for (auto it : items) {
                objects[it->get_id()] = it;
                if (it->get_type() == ItemType::Key) {
                    keys.push_back(Key::cast(it));
                }
            }
        }
    }

    //TODO: keys to doors
}

WallType get_walltype(const bool* code) {
    if (code[0] && code[1] && code[2] && code[3] && code[4] && code[5] && code[6] && code[7]) {
        return WallType::filled;
    }
    if (code[0] && code[2] && code[4] && code[6]) {
        if (code[1] && code[3] && code[5]) return WallType::ru_corner;
        if (code[3] && code[5] && code[7]) return WallType::rb_corner;
        if (code[5] && code[7] && code[1]) return WallType::lb_corner;
        if (code[7] && code[1] && code[3]) return WallType::lu_corner;
        if ((code[1] && code[5]) || (code[3] && code[7])) return WallType::cross;
        if (code[1] && code[3]) return WallType::t_down;
        if (code[3] && code[5]) return WallType::t_left;
        if (code[5] && code[7]) return WallType::t_up;
        if (code[7] && code[1]) return WallType::t_right;
        return WallType::cross;
    }
    if (code[0] && code[2] && code[4] && (!code[1] || !code[3])) return WallType::t_up;
    if (code[2] && code[4] && code[6] && (!code[3] || !code[5])) return WallType::t_right;
    if (code[4] && code[6] && code[0] && (!code[5] || !code[7])) return WallType::t_down;
    if (code[6] && code[0] && code[2] && (!code[7] || !code[1])) return WallType::t_left;
    if (code[0] && code[4]) return WallType::horizontal;
    if (code[2] && code[6]) return WallType::vertical;
    if (code[0] && code[2]) return WallType::rb_corner;
    if (code[2] && code[4]) return WallType::lb_corner;
    if (code[4] && code[6]) return WallType::lu_corner;
    if (code[6] && code[0]) return WallType::ru_corner;
    if (code[0] || code[4]) return WallType::horizontal;
    if (code[2] || code[6]) return WallType::vertical;
    return WallType::single;
}

void Core::init_tiles() {
    int w = map_info.size.x;
    int h = map_info.size.y;
    for (int i = 0; i < w; ++i) {
        for(int j = 0; j < h; ++j) {
            TilePtr tile = get_tile(Coord(i, j));
            if (tile->get_type() == TileType::Wall) {
                auto wall_tile = WallTile::cast(tile);
                bool code[8];
                int x = i;
                int y = j;
                int dx = 1;
                int dy = 1;
                TilePtr around_tiles[8] = {
                    get_tile(Coord(x, y - dy)),
                    get_tile(Coord(x - dx, y - dy)),
                    get_tile(Coord(x - dx, y)),
                    get_tile(Coord(x - dx, y + dy)),
                    get_tile(Coord(x, y + dy)),
                    get_tile(Coord(x + dx, y + dy)),
                    get_tile(Coord(x + dx, y)),
                    get_tile(Coord(x + dx, y - dy))
                };
                for (int k = 0; k < 8; ++k) {
                    code[k] = around_tiles[k]->get_type() == TileType::Wall || around_tiles[k]->get_immovables().size();
                }
                wall_tile->set_walltype(get_walltype(code));
            }
        }
    }
}

void Core::wait() {
    make_turn();
}

UnitPtr Core::get_enemy() {
    return near_enemy;
}

void Core::make_turn() {
    for(auto a : actable) {
        a.second->act();
    }
}

HeroPtr Core::get_hero() {
    return hero;
}

Result Core::move_hero(Direction dir) {
    TilePtr tile_from = hero->get_pos();
    TilePtr tile_to   = get_tile(get_coord(tile_from).move(dir));
    ActionPtr action;
    
    std::vector<ImmovablePtr> imms = tile_to->get_immovables();
    UnitPtr unit = tile_to->get_unit();
    std::vector<ItemPtr> tile_items = tile_to->get_items();
    if (unit) {
        Impact impact = hero->get_impact();
        action = Atack::New(hero, unit, impact);
    } else if (imms.size()) {
        DoorPtr door = Door::cast(imms[0]);
        if (!door->is_open()) {
            std::vector<ItemPtr> items = hero->get_items();
            for(auto it : items) {
                if (door->Open(it->get_id()) == Result::Success) {
                    hero->drop_item(it->get_id());
                    make_turn();
                    return Result::Success;
                }
            }
            return Result::Failure;
        } else {
            action = Move::New(hero, tile_to);
        }
    } else if (tile_items.size()) {
        ItemPtr item = tile_items.back();
        action = Pick::New(hero, item);
        tile_to->take_item(item->get_id());
    } else {
        action = Move::New(hero, tile_to);
    }

    Result res = do_action(action);
    if (res == Result::Success) {
        make_turn();
    }
    return res;
}

Coord Core::get_coord(TilePtr tile) {
    return tiles[tile];
}

TilePtr Core::get_tile(Coord c) {
    if (c.x < 0 || c.x >= (int)map.size() || c.y < 0 || c.y >= (int)map[c.x].size())
        return std::make_shared<WallTile>();
    return map[c.x][c.y];
}

void Core::subscribe_map(std::function<void(Coord)> f) {
    map_updater = f;
}

void Core::subscribe_action(std::function<void(ActionPtr)> f) {
    action_updater = f;
}

Result Core::do_move(MovePtr action) {
    UnitPtr actor = action->get_actor();
    TilePtr tile_to = action->get_tile();
    TilePtr tile_from = actor->get_pos();

    if (!tile_to->free()) {
        return Result::Failure;
    }
    tile_from->move_from();
    tile_to->move_to(actor);
    
    return Result::Success;
}

Result Core::do_atack(AtackPtr action) {
    ActableObjPtr actor = action->get_actor();
    UnitPtr reactor = action->get_reactor();
    
    Impact impact = action->get_impact();
    Avoidance avoid = reactor->get_avoidance();

    int damage = battle_system.calculate_damage(impact, avoid);
    
    reactor->take_damage(damage, actor);

    return Result::Success;
}

Result Core::do_interact(InteractPtr action) {
    UnitPtr actor = action->get_actor();
    ActableObjPtr reactor = action->get_reactor();
    reactor->react(action);
    return Result::Success;
}

Result Core::do_pick(PickPtr action) {
    UnitPtr who = action->get_actor();
    ItemPtr what = action->get_item();

    who->pick_item(what);
    return Result::Success;
}

Result Core::do_die(DiePtr action) {
    ActableObjPtr actor = action->get_actor();
    ActableObjPtr reactor = action->get_reactor();

    TilePtr place_of_death = actor->get_pos();
    if (place_of_death->get_unit()->get_id() == actor->get_id()) {
        place_of_death->move_from();
    } else {
        place_of_death->del_immovable(actor->get_id());
    }

    objects.erase(actor->get_id());
    actable.erase(actor->get_id());
    return Result::Success;
}

Result Core::do_action(ActionPtr action) {
    switch(action->get_type()) {
        case ActionType::Move:
            return do_move(Move::cast(action));
            break;
        case ActionType::Atack:
            return do_atack(Atack::cast(action));
            break;
        case ActionType::Pick:
            return do_pick(Pick::cast(action));
            break;
        case ActionType::Interact:
            return do_interact(Interact::cast(action));
            break;
        case ActionType::Die:
            return do_die(Die::cast(action));
            break;
    }
    return Result::Failure;
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

