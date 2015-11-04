#pragma once
#include <iostream>
#include <vector>
#include <unistd.h>
#include <string>
#include <ncurses.h>
#include "core.h"
#include "utils.h"
#include "math.h"
#include "consoleprint.h"
#include "drawinfo.h"
#include <map>

using namespace std;

class ConsoleGraphics
{
    int console_size_y;
    int console_size_x;
    int height;
    int width;
    int shift;
    DrawInfo info;
    map <string, string> codes;

    //"\u2D65" монстр  "\u2E19" - дерево 9879  9608

public:
    ConsoleGraphics ();
    void init ();
    void draw_wall ();
    string GetRenderCellSymbolWall(int r, int c);
    void draw_hero_stats ();
    void draw_coin (Coord x);
    void draw_door (Coord x);
    void draw_hero ();
    void refresh ();

    void draw_in_window (Coord x, string symb_code, int color);
    void move_hero_right ();
    void move_hero_up();
    void move_hero_left();
    void move_hero_down();

    ~ConsoleGraphics ();


};
