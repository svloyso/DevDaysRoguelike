#pragma once
#include <iostream>
#include <vector>
#include <unistd.h>
#include <string>
#include <ncurses.h>
#include "math.h"
#include "consoleprint.h"
#include "drawinfo.h"
#include <map>
#include "cuttingwindow.h"
#include "core.h"
#include "hero.h"
#include "utils.h"

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
    Coord game_play_point;
    CuttingWindow game_play;
    int game_play_width;
    int game_play_height;

    //"\u2D65" монстр  "\u2E19" - дерево 9879  9608
public:
    ConsoleGraphics ();
    void init ();
    void draw_wall ();
    void draw_wall (Coord c, int h, int w);
    string get_render_cell_symbol_wall (int r, int c);
    void draw_hero_stats ();
    void draw_coin (Coord x);
    void draw_door (Coord x);
    void draw_hero ();
    void refresh ();
    void init_map ();
    void draw_in_window (Coord x, string symb_code, int color);
    void move_hero_right ();
    void move_hero_up ();
    void move_hero_left ();
    void move_hero_down ();

    ~ConsoleGraphics ();


};
