#include <vector>
#include <string>
#include <sstream>

#include "base_window.h"
#include "play_window.h"
#include "stat_window.h"
#include "log_window.h"
#include "chrs_window.h"
#include "hero.h"
#include "item.h"


void BaseWindow::print_long_line(std::string str) {

}

void ChrsWindow::refresh_window() {
    HeroPtr hero = main_core->get_hero();
    UnitStats stats = hero->get_stats();
    auto items = hero->get_items();
    ClothesPtr head = hero->get_head();
    ClothesPtr body = hero->get_body();
    ClothesPtr legs = hero->get_legs();
    WeaponPtr weapon = hero->get_weapon();
    
    int x = 0, y = 0;
    mvwprintw(win, y, x, "Сила: %d", int(stats.strength));
    getyx(win, y, x);
    if (x != 0) {
        y += 1; x = 0;
    }
    mvwprintw(win, y, x, "Ловкость: %d", int(stats.agility));
    getyx(win, y, x);
    if (x != 0) {
        y += 1; x = 0;
    }
    mvwprintw(win, y, x, "Снаряжение:");
    getyx(win, y, x);
    if (x != 0) {
        y += 1; x = 0;
    }
    mvwprintw(win, y, x, "Голова: %s", head->get_name().c_str());
    getyx(win, y, x);
    if (x != 0) {
        y += 1; x = 0;
    }
    mvwprintw(win, y, x, "Тело: %s", body->get_name().c_str());
    getyx(win, y, x);
    if (x != 0) {
        y += 1; x = 0;
    }
    mvwprintw(win, y, x, "Ноги: %s", legs->get_name().c_str());
    getyx(win, y, x);
    if (x != 0) {
        y += 1; x = 0;
    }
    mvwprintw(win, y, x, "Оружие: %s", weapon->get_name().c_str());
    
    wrefresh(win);
}


void PlayWindow::refresh_window() {
    PaintVisitor vis;
    HeroPtr hero = main_core->get_hero();
    TilePtr h_tile = hero->get_pos();
    Coord   h_coord = h_tile->get_coord();
    int from_y = h_coord.x - height / 2;
    int to_y   = from_y + height;
    int from_x = h_coord.y - width / 2;
    int to_x   = from_x + width;
    for (int x = from_x; x < to_x; ++x) {
        for(int y = from_y; y < to_y; ++y) {
            TilePtr tile = main_core->get_tile(Coord(y, x));
            vis.visit(tile);
            const char* res = vis.get_val();
            int fg = vis.get_fg();
            int bg = vis.get_bg();
            wattron(win, COLOR_PAIR(get_colorpair(fg, bg)));
            mvwprintw(win, y - from_y, x - from_x, res);
            wattroff(win, COLOR_PAIR(get_colorpair(COLOR_WHITE, COLOR_BLACK)));
        }
    }
    wrefresh(win);
}


void StatWindow::print_hpline(int hp, int max_hp, int pos_y, int pos_x, int size) {
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

void StatWindow::refresh_window() {
    std::stringstream ss;
    HeroPtr hero = main_core->get_hero();
    wclear(win);
    if (hero) {
        std::string hero_name = hero->get_name();

        int hero_hp = hero->get_stats().hit_points;
        int hero_maxhp = hero->get_stats().max_hit_points;
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
    if(enemy && enemy->get_stats().hit_points > 0) {
        std::string enemy_name = enemy->get_name();
    
        int enemy_hp = enemy->get_stats().hit_points;
        int enemy_maxhp = enemy->get_stats().max_hit_points;
        ss.str(""); ss.clear(); ss << enemy_hp << "/" << enemy_maxhp;

        wattron(win, COLOR_PAIR(get_colorpair(COLOR_RED, COLOR_BLACK)));
        mvwprintw(win, 0, enemyhp_pos, enemy_name.c_str());
        wattron(win, COLOR_PAIR(get_colorpair(COLOR_WHITE, COLOR_BLACK)));
        mvwprintw(win, 1, enemyhp_pos, ss.str().c_str());
        print_hpline(enemy_hp, enemy_maxhp, 2, enemyhp_pos, 20);
    } 

    wrefresh(win);
}


void LogWindow::refresh_window() {
    mvwprintw(win, 0, 0, "Здесь будет лог!");
    wrefresh(win);
}

