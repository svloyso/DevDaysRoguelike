#ifndef DRAWINFO_H
#define DRAWINFO_H
#include "coord.h"
#include "consoleprint.h"
using namespace  std;
class DrawInfo
{
    int hero_max_hp;
    int hero_cur_hp;
    double norma;
    int one_part_hp;
    int full_parts_count;
    int fractions_count;

public:
    void draw_hp_line ();
    DrawInfo (int _hero_max_hp = 400, int _hero_cur_hp = 400);
    void draw_hero_stats (int _hero_cur_hp = 400);
    void draw_hp();
    void draw_empty_hp_line ();
    void draw_full_hp_line ();
    void draw_green_hp_line ();
    int compute_diff ();
    void draw_one_part (int color);
};

#endif // DRAWINFO_H
