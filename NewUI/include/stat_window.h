#pragma once
#include "common.h"
#include "hero.h"
#include "unit.h"

class StatWindow {
public:
    StatWindow(int _height, int _width, int y, int x, bool with_bord = true) : width(_width), height(_height), bord(NULL) 
    {
        if (with_bord) {
            bord = newwin(height + 2, width + 2, y - 1, x - 1);
            box(bord, 0, 0);
            refresh();
            wrefresh(bord);
        }
        refresh();
        win = newwin(_height, _width, y, x); 
        wrefresh(win);
    }
    void print_hpline(int hp, int max_hp, int pos_y, int pos_x, int size) {
        wattron(win, COLOR_PAIR(get_colorpair(COLOR_WHITE, COLOR_BLACK)));
        for(int i = 1; i < size; ++i) {
            mvwprintw(win, pos_y, pos_x + i, "\u2585");
        }

        double perc = (double)hp/max_hp;
        int color;
        if (perc > 0.75) {
            color = COLOR_GREEN;
        } else if (perc > 0.25) {
            color = COLOR_YELLOW;
        } else {
            color = COLOR_RED;
        }
        wattron(win, COLOR_PAIR(get_colorpair(color, COLOR_BLACK)));
        int pos = pos_x;
        while(perc >= 0) {
            mvwprintw(win, pos_y, pos++, "\u2585");
            perc -= 1.0 / size;
        }
    }

    void refresh_window() {
        std::stringstream ss;
        HeroPtr hero = main_core->get_hero();
        wclear(win);
        if (hero) {
            std::string hero_name = hero->get_name();

            int hero_hp = hero->get_stats()->hit_points;
            int hero_maxhp = hero->get_stats()->max_hit_points;
            ss << hero_hp << "/" << hero_maxhp;
            
            wattron(win, COLOR_PAIR(get_colorpair(COLOR_WHITE, COLOR_BLACK)));
            mvwprintw(win, 0, 0, hero_name.c_str());
            move(1, 0);
            wclrtoeol(win);
            mvwprintw(win, 1, 0, ss.str().c_str());
            print_hpline(hero_hp, hero_maxhp, 2, 0, 20);
        }

        int enemyhp_pos = 30;
        UnitPtr enemy = main_core->get_enemy();
        if(enemy && enemy->get_stats()->hit_points > 0) {
            std::string enemy_name = enemy->get_name();
        
            int enemy_hp = enemy->get_stats()->hit_points;
            int enemy_maxhp = enemy->get_stats()->max_hit_points;
            ss.str(""); ss.clear(); ss << enemy_hp << "/" << enemy_maxhp;

            wattron(win, COLOR_PAIR(get_colorpair(COLOR_RED, COLOR_BLACK)));
            mvwprintw(win, 0, enemyhp_pos, enemy_name.c_str());
            wattron(win, COLOR_PAIR(get_colorpair(COLOR_WHITE, COLOR_BLACK)));
            mvwprintw(win, 1, enemyhp_pos, ss.str().c_str());
            print_hpline(enemy_hp, enemy_maxhp, 2, enemyhp_pos, 20);
        } 

        wrefresh(win);
    }


private:
    int width;
    int height;
    WINDOW* win;
    WINDOW* bord;
};
