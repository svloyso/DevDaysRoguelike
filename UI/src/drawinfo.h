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

public:
    void draw_hp_line ();
    DrawInfo(int _hero_max_hp = 400, int _hero_cur_hp = 400);
    void draw_hero_stats (int _hero_cur_hp = 400);
    void draw_hp();
    void draw_full_hp_line ();
    void draw_mid_hp_line ();
};

#endif // DRAWINFO_H
