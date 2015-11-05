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
#include "unit.h"

using namespace std;

class ConsoleGraphics
{
    int console_size_y;
    int console_size_x;
    int height;
    int width;
    int shift;
    Coord game_play_point;
    CuttingWindow game_play;
    int game_play_width;
    int game_play_height;

    Coord stats_point;
    CuttingWindow stats_window;
    int stats_width;
    int stats_height;
    DrawInfo info;

    Coord invent_point;
    CuttingWindow invent_window;
    int invent_width;
    int invent_height;


    //"\u2D65" монстр  "\u2E19" - дерево 9879  9608 
public:
    ConsoleGraphics ();
    void init ();
    void draw_wall (Coord c, int h, int w);
    void draw_hero_stats ();
    void draw_door (Coord x);
    void draw_hero ();
    void refresh ();
    bool is_alive ();
    void move_hero_right ();
    void move_hero_up ();
    void move_hero_left ();
    void move_hero_down ();

    ~ConsoleGraphics ();


};
