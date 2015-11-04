#pragma once
#include <memory>
#include <vector>

#include "basic.h"
#include "unit.h"
#include "item.h"
#include "coord.h"
#include "tile_fwd.h"

class Tile : public Object {
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

    static TilePtr to_TilePtr(ObjectPtr obj);
protected:
    std::vector<ItemPtr> items;
    std::vector<ImmovablePtr> immovables;
    UnitPtr unit;
};

class WallTile : public Tile {
public:
    WallTile(UnitPtr _unit = UnitPtr(), 
             const std::vector<ItemPtr>& items = std::vector<ItemPtr>(), 
             const std::vector<ImmovablePtr>& immovables = std::vector<ImmovablePtr>()) 
        : Tile(_unit, items, immovables) 
    {}
    TileType get_type() { return TileType::Wall; }
    bool free() { return false; }
    virtual Result put_item(ItemPtr item) { return Result::Failure; }
    virtual Result take_item(int item_id) { return Result::Failure; }
    virtual Result move_to(UnitPtr unit)  { return Result::Failure; }
    virtual Result move_from() { return Result::Failure; }
    virtual Result add_immovable(ImmovablePtr imm) { return Result::Failure; }
    virtual Result del_immovable(int imm_id) { return Result::Failure; }
};

class FloorTile: public Tile {
public:
    FloorTile(UnitPtr _unit = UnitPtr(), const std::vector<ItemPtr>& items = std::vector<ItemPtr>(), const std::vector<ImmovablePtr>& immovables = std::vector<ImmovablePtr>()) : Tile(_unit, items, immovables)  {}
    TileType get_type() { return TileType::Floor; }
};

