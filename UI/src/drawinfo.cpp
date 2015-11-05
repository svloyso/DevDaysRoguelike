#include "drawinfo.h"
#include <iostream>
#include <sstream>

using namespace std;

DrawInfo::DrawInfo(CuttingWindow _stat_wind)
    : stat_wind (_stat_wind)
{
}

void DrawInfo::enemy_draw_stats (int _enemy_cur_hp, int _enemy_max_hp, string _name)
{
    enemy_cur_hp = _enemy_cur_hp;
    enemy_max_hp = _enemy_max_hp;
    name = _name;
    Coord x (1, 35);
    stat_wind.print (x, name, 31);
    x = Coord (2, 35);
    stat_wind.print (x, "               ", 35);
    std::stringstream ss1;
    ss1 << "HP: " << enemy_cur_hp << "/" << enemy_max_hp;
    stat_wind.print (x, ss1.str(), 15);
     draw_empty_hp_line_enemy ();
     cout <<  "\033[0m";
    cout << "\033[5;35H"<<  "\033[0m" << "|";
    if (enemy_cur_hp <= enemy_max_hp / 5)
    {
        for (int i = 1; i <= enemy_cur_hp / 10; i++)
        {
            if (i % 4 == 0)
                cout <<  "\033[0m" << "|";
            else cout << "\033[41m" << " "; // red
        }
        cout <<  "\033[0m";
        return;
    }
    cout << "\033[5;35H" <<  "\033[0m" << "|";
    for (int i = 1; i <= enemy_cur_hp / 10; i++)
    {
        if (i % 4 == 0)
            cout <<  "\033[0m" << "|";
        else cout  << "\033[43m" << " "; // yellow

    }
    cout <<  "\033[0m";
}
void DrawInfo::hero_draw_stats (int _hero_cur_hp, int _hero_max_hp)
{
    hero_cur_hp = _hero_cur_hp;
    hero_max_hp = _hero_max_hp;
    std::stringstream ss;
    Coord x (1, 2);
    stat_wind.print (x, "HERO", 31);
    x = Coord (2, 2);
    stat_wind.print (x, "               ", 35);
    ss << "HP: " << hero_cur_hp << "/" << hero_max_hp;
    stat_wind.print (x, ss.str(), 15);
     
    if (hero_cur_hp == hero_max_hp)
    {
        draw_full_hp_line();
        return;
    }
    draw_empty_hp_line ();
    cout << "\033[5;3H"<<  "\033[0m" << "|";
    if (hero_cur_hp <= hero_max_hp / 5)
    {
        for (int i = 1; i <= hero_cur_hp / 20; i++)
        {
            if (i % 4 == 0)
                cout <<  "\033[0m" << "|";
            else cout << "\033[41m" << " "; // red
        }
        cout <<  "\033[0m";
        return;
    }
    cout << "\033[5;3H" <<  "\033[0m" << "|";
    for (int i = 1; i <= hero_cur_hp / 20; i++)
    {
        
        if (i % 4 == 0)
            cout <<  "\033[0m" << "|";
        else cout  << "\033[43m" << " "; // yellow
    }
     cout <<  "\033[0m";
}
 
void DrawInfo::draw_empty_hp_line ()
{
        cout << "\033[5;3H" << "|" <<  "\033[00m";
        cout << "   "<<  "\033[100m" << "|";
        cout << "   "<<  "\033[100m" << "|";
        cout << "   "<<  "\033[100m" << "|";
        cout << "   "<<  "\033[100m" << "|";
        cout << "   "<<  "\033[100m" << "|";

}
void DrawInfo::clear_enemy_info()
{
    Coord x (1, 35);
     stat_wind.print (x, "               ", 35);
    x = Coord (2, 35);
    stat_wind.print (x, "               ", 35);
    draw_empty_hp_line_enemy ();
}
void DrawInfo::draw_empty_hp_line_enemy ()
{
        cout << "\033[5;35H" << "|" <<  "\033[00m";
        cout << "   "<<  "\033[100m" << "|";
        cout << "   "<<  "\033[100m" << "|";
        cout << "   "<<  "\033[100m" << "|";
        cout << "   "<<  "\033[100m" << "|";
        cout << "   "<<  "\033[100m" << "|";

}
void DrawInfo::draw_full_hp_line ()
{
        cout << "\033[5;3H" << "|";
        cout << "\033[42m" << "   "<<  "\033[00m" << "|";
        cout << "\033[42m" << "   "<<  "\033[00m" << "|";
        cout << "\033[42m" << "   "<<  "\033[00m" << "|";
        cout << "\033[42m" << "   "<<  "\033[00m" << "|";
        cout << "\033[42m" << "   "<<  "\033[00m" << "|";
}
void DrawInfo::draw_full_hp_line_enemy ()
{
            cout << "\033[5;35H" << "|";
        cout << "\033[42m" << "   "<<  "\033[00m" << "|";
        cout << "\033[42m" << "   "<<  "\033[00m" << "|";
        cout << "\033[42m" << "   "<<  "\033[00m" << "|";
        cout << "\033[42m" << "   "<<  "\033[00m" << "|";
        cout << "\033[42m" << "   "<<  "\033[00m" << "|";
}
