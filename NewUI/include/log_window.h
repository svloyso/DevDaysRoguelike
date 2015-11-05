#pragma once
#include <ncurses.h>

class LogWindow {
public:
    LogWindow(int _height, int _width, int y, int x, bool with_bord=true) : width(_width), height(_height), win(newwin(_height, _width, y, x)), bord(NULL) 
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
        mvwprintw(win, 0, 0, "Здесь будет лог!");
        wrefresh(win);
    }
private:
    int width;
    int height;
    WINDOW* win;
    WINDOW* bord;
};
