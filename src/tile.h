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
        virtual Coord get_coord();
        virtual void  set_coord(Coord _c);
    private:
        std::vector<ItemPtr> items;
        std::vector<UnitPtr> units;
        TileType type;
        Coord c;
};

typedef std::shared_ptr<Tile> TilePtr;

