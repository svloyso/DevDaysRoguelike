#pragma once
#include <ncurses.h>
#include "common.h"
#include "paint_visitor.h"
#include "hero.h"
#include "tile.h"
#include "core.h"
#include "base_window.h"

class PlayWindow : public BaseWindow {
public:
    PlayWindow(int _height, int _width, int y, int x, bool with_bord=true) :  BaseWindow(_height, _width, y, x, with_bord) {}    
    
    void refresh_window();
    
};


