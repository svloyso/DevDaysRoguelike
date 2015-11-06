#pragma once
#include <ncurses.h>
#include "base_window.h"

class LogWindow : public BaseWindow{
public:
    LogWindow(int _height, int _width, int y, int x, bool with_bord=true) : BaseWindow(_height, _width, y, x, with_bord) {} 

    void refresh_window();

};
