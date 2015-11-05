#ifndef DRAWINFO_H
#define DRAWINFO_H
#include "utils.h"
#include "consoleprint.h"
#include "cuttingwindow.h"

using namespace  std;
class DrawInfo
{
    int hero_max_hp;
    int hero_cur_hp;
    double norma;
    int one_part_hp;
    int full_parts_count;
    int fractions_count;
    CuttingWindow stat_wind;
    int enemy_cur_hp;
     int enemy_max_hp;

public:
    void draw_hp_line ();
    DrawInfo (CuttingWindow _stat_wind);
    void hero_draw_stats ();
    void enemy_draw_stats ();
    void draw_hp (int _cur_hp, int _hero_max_hp, int enemy_cur_hp, int _enemy_max_hp);
    void draw_empty_hp_line ();
    void draw_full_hp_line ();
    void draw_full_hp_line_enemy ();
    void draw_empty_hp_line_enemy ();
};

#endif // DRAWINFO_H
