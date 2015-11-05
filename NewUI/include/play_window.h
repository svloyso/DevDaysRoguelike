#pragma once
#include <ncurses.h>
#include "common.h"
#include "paint_visitor.h"
#include "hero.h"
#include "tile.h"
#include "core.h"

class PlayWindow {
public:
    PlayWindow(int _height, int _width, int y, int x, bool with_bord=true) : height(_height), width(_width), win(newwin(height, width, y, x)), bord(NULL)
    {
        if (with_bord) {
            bord = newwin(height+2, width+2, y - 1, x - 1);
            box(bord, 0, 0);
            refresh();
            wrefresh(bord);
        }
        wrefresh(win);
    }

    void refresh_window() {
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

private:
    int height;
    int width;
    WINDOW* win;
    WINDOW* bord;
};

