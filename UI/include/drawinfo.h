#ifndef DRAWINFO_H
#define DRAWINFO_H
#include "utils.h"
#include "consoleprint.h"
#include "cuttingwindow.h"
#include <string>
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
     string name;

public:
    DrawInfo (CuttingWindow _stat_wind);
    void hero_draw_stats (int _cur_hp, int _hero_max_hp);
    void enemy_draw_stats (int _enemy_cur_hp, int _enemy_max_hp, string _name);
    void draw_empty_hp_line ();
    void draw_full_hp_line ();
    void draw_full_hp_line_enemy ();
    void draw_empty_hp_line_enemy ();
    void clear_enemy_info();
};

#endif // DRAWINFO_H
