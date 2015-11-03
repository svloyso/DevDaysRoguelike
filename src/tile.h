#pragma once
#include <memory>

#include "basic.h"
#include "unit.h"
#include "item.h"
#include "coord.h"

enum class TileType {
    Wall,
    Floor
};

class Tile : public VisibleObject {
public:
    TileType getType();
    virtual std::vector<ItemPtr> get_items();
    virtual std::vector<UnitPtr> get_units();
private:
    std::vector<ItemPtr> items;
    std::vector<UnitPtr> units;
};

class WallTile : public Tile {
    WallTile() {}
    TileType getType() { return TileType::Wall; }
};

class FloorTile: public Tile {
    FloorTile() {}
    TileType getType() { return TileType::Floor; }
};

typedef std::shared_ptr<Tile> TilePtr;
typedef std::shared_ptr<WallTile> WallTilePtr;
typedef std::shared_ptr<FloorTile> FloorTilePtr;

