#pragma once
#include "common.h"
#include "hero.h"
#include "unit.h"
#include "base_window.h"

class StatWindow : public BaseWindow {
public:
    StatWindow(int _height, int _width, int y, int x, bool with_bord = true) : BaseWindow(_height, _width, y, x, with_bord) {} 
    void refresh_window();
protected:
    void print_hpline(int hp, int max_hp, int pos_y, int pos_x, int size);
};
