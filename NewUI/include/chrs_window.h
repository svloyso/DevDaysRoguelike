#pragma once
#include <ncurses.h>
#include "core.h"
#include "stats.h"

class ChrsWindow {
public:
    ChrsWindow(int _height, int _width, int y, int x, bool with_bord = true) : width(_width), height(_height), win(newwin(_height, _width, y, x)), bord(NULL) 
    {
        if (with_bord) {
            bord = newwin(height + 2, width + 2, y - 1, x - 1);
            box(bord, 0, 0);
            refresh();
            wrefresh(bord);
        }
        wrefresh(win);
    }
    void refresh_window() {
        HeroPtr hero = main_core->get_hero();
        HeroStats* stats = hero->get_stats();
        mvwprintw(win, 0, 1, "Сила: %d", stats->strength);
        mvwprintw(win, 1, 1, "Ловкость: %d", stats->agility);
        mvwprintw(win, 3, 1, "Снаряжение:");
        mvwprintw(win, 4, 1, "Голова: Шлем викинга");
        mvwprintw(win, 5, 1, "Тело: Фуфайка");
        mvwprintw(win, 6, 1, "Оружие: Перочинный нож");
        mvwprintw(win, 7, 1, "Ноги: Валенки с калошами");
        wrefresh(win);
    }
private:
    int width;
    int height;
    WINDOW* win;
    WINDOW* bord;
};
