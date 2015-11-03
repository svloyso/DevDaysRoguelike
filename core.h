#pragma once
#include <vector>
#include <memory>
#include <functional>

#include "tile.h"
#include "action.h"
#include "coord.h"

class Core {
public:
    TilePtr get_tile(Coord c, int j);
    void set_tile(Coord c, TilePtr t);
    void subscribe_map(std::function<void(Coord, TilePtr)> f);
    void subscribe_action(std::function<void(ActionPtr)> f);
    void do_action(ActionPtr action);
};
