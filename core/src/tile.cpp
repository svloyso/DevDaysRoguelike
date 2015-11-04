#include "tile.h"
#include "core.h"

bool Tile::free() {
    if (unit) return false;
    return true;
}

UnitPtr Tile::get_unit() {
    return unit;
}

std::vector<ItemPtr> Tile::get_items() { 
    return items; 
}

std::vector<ImmovablePtr> Tile::get_immovables() { 
    return immovables;
}

Result Tile::add_immovable(ImmovablePtr imm) {
    immovables.push_back(imm);
    return Result::Success;
}

Result Tile::del_immovable(int imm_id) {
    for(size_t i = 0; i < immovables.size(); ++i) {
        if (immovables[i]->get_id() == imm_id) {
            immovables.erase(immovables.begin() + i);
            return Result::Success;
        }
    }
    return Result::Failure;
}

Result Tile::put_item(ItemPtr item) { 
    items.push_back(item); 
    return Result::Success;
}

Result Tile::move_to(UnitPtr _unit) { 
    if (unit) { return Result::Failure; }
    unit = _unit;
    unit->set_pos(Tile::to_TilePtr(main_core->get_object(this->get_id())));
    return Result::Success;
}

Result Tile::take_item(int item_id) {
    for(size_t i = 0; i < items.size(); ++i) {
        if (items[i]->get_id() == item_id) {
            items.erase(items.begin() + i);
            return Result::Success;
        }
    }
    return Result::Failure;
}

Result Tile::move_from() {
    if (!unit) { return Result::Failure; }
    unit = UnitPtr();
    return Result::Success;
}


