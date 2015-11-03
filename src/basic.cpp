#include "basic.h"
#include "core.h"

int Object::next_id = 0;

Coord VisibleObject::get_coord() {
    return main_core.get_object_coord(get_id());
}

