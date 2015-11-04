#pragma once
#include <iostream>
#include <unistd.h>
#include <vector>
#include <string>
#include <ncurses.h>
#include "core_mock.h"
#include "coord.h"
#include "math.h"
using namespace std;

class ConsoleGraphics
{
    int console_size_y;
    int console_size_x;
    int height;
    int width;
    int shift;
    Coord hero_pos;
    CoreMock core_mock;

public:
    ConsoleGraphics ();
    void init();
    void draw_wall ();
    void clear_screen ();
    void print_symbol (Coord x, string symb_code, int color, int bg_color = 30);
    void print_string (Coord x, string str, int color);
    void draw_hero_stats ();
    void draw_coin (Coord x);
    void draw_hero ();
    void refresh ();
    void draw_hp_line (int max_hp, int cur_hp);
    void draw_in_window (Coord x, string symb_code, int color, int bg_color = 30);
    void move_hero_right ();
    void move_hero_up();
    void move_hero_left();
    void move_hero_down();
    void set_cursor_in_win_center ();
    ~ConsoleGraphics ();
};
