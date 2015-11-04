#include "visitor.h"
#include "basic.h"

void Visitor::visit(ObjectPtr obj) {
    obj->visit(this);
}

