#pragma once
#include <memory>

#include "basic.h"

enum class TileType {
    Wall,
    Floor
};

class Tile : public VisibleObject {
    public:
        TileType getType();
        const std::vector<ItemPtr>& get_items();
        const std::vector<UnitPtr>& get_units();

    private:
        std::vector<ItemPtr> items;
        std::vector<UnitPtr> units;
        TileType type;
};

typedef std::shared_ptr<Tile> TilePtr;

