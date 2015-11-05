#pragma once
#include <memory>
#include <vector>
#include <map>
#include "basic.h"
#include "unit.h"
#include "item.h"
#include "utils.h"
#include "tile_fwd.h"
#include "visitor.h"
#include "core_fwd.h"

class Tile : public Object {
    friend class Core;
public:
    Tile(
        UnitPtr _unit, 
        const std::vector<ItemPtr>& _items, 
        const std::vector<ImmovablePtr>& _immovables
    ) : items(_items), 
        immovables(_immovables), 
        unit(_unit) 
    {}
    virtual TileType get_type() = 0;
    virtual std::vector<ItemPtr> get_items();
    virtual std::vector<ImmovablePtr> get_immovables();
    virtual UnitPtr get_unit();
    virtual Result put_item(ItemPtr item);
    virtual Result take_item(int item_id);
    virtual Result add_immovable(ImmovablePtr immovable);
    virtual Result del_immovable(int immov_id);
    virtual Result move_to(UnitPtr unit);
    virtual Result move_from();
    virtual bool free();

    virtual Coord get_coord();
    
    DECLARE_VISIT(Tile)
    DECLARE_COMMON_METHODS(Tile)
protected:
    std::vector<ItemPtr> items;
    std::vector<ImmovablePtr> immovables;
    UnitPtr unit;
};

enum class WallType {
    lu_corner,
    ru_corner,
    lb_corner,
    rb_corner,
    horizontal,
    vertical,
    cross,
    t_down,
    t_up,
    t_right,
    t_left,
    filled,
    single
};

class WallTile : public Tile {
public:
    WallTile(UnitPtr _unit = UnitPtr(), 
             const std::vector<ItemPtr>& _items = std::vector<ItemPtr>(), 
             const std::vector<ImmovablePtr>& _immovables = std::vector<ImmovablePtr>()) 
        : Tile(_unit, _items, _immovables), type(WallType::filled)
    {}
    TileType get_type() { return TileType::Wall; }
    bool free() { return false; }
    virtual Result put_item(ItemPtr item) { return Result::Failure; }
    virtual Result take_item(int item_id) { return Result::Failure; }
    virtual Result move_to(UnitPtr unit)  { return Result::Failure; }
    virtual Result move_from() { return Result::Failure; }
    virtual Result add_immovable(ImmovablePtr imm) { return Result::Failure; }
    virtual Result del_immovable(int imm_id) { return Result::Failure; }

    WallType get_walltype() { return type; }
    void set_walltype(WallType _type) { type = _type; }

    DECLARE_COMMON_METHODS(WallTile)
    DECLARE_VISIT(WallTile)
private:
    WallType type;
};

class FloorTile: public Tile {
public:
    FloorTile(UnitPtr _unit = UnitPtr(), const std::vector<ItemPtr>& _items = std::vector<ItemPtr>(), const std::vector<ImmovablePtr>& _immovables = std::vector<ImmovablePtr>()) : Tile(_unit, _items, _immovables)  {}
    TileType get_type() { return TileType::Floor; }

    

    DECLARE_VISIT(FloorTile)
    DECLARE_COMMON_METHODS(FloorTile)
};

