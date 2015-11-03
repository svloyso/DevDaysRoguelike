#pragma once
#include <memory>

#include "basic.h"

class Item : public VisibleObject {
    public:
        Item();
};

typedef std::shared_ptr<Item> ItemPtr;
