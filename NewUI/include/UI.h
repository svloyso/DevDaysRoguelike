#pragma once
#include <ncurses.h>
#include <locale.h>
#include <map>
#include <sstream>

#include "common.h"
#include "play_window.h"
#include "stat_window.h"
#include "log_window.h"
#include "chrs_window.h"

class UI {

public:
    UI() {
       init(); 
    }

    ~UI() {
        endwin();
    }

    void init() {
        setlocale(LC_ALL, "");
        initscr();
	    cbreak();
        noecho();
        curs_set(0);
        init_windows();
        init_palette();
        refresh();
    }

    void init_palette() {
        start_color();
        int k = 1;
        for(int fg = 0; fg < 8; ++fg) {
            for(int bg = 0; bg < 8; ++bg) {
                init_pair(k++, fg, bg);
            }
        }
    }

    void play() {
        play_win->refresh_window();
        stat_win->refresh_window();
        log_win->refresh_window();
        chrs_win->refresh_window();
        int ch;
        while( (ch = getch()) != 'q' ) {
            switch(ch) {
                case 'k':
                case 'w':
                    main_core->move_hero(Direction::Left);
                    break;
                case 'j':
                case 's':
                    main_core->move_hero(Direction::Right);
                    break;
                case 'l':
                case 'd':
                    main_core->move_hero(Direction::Up);
                    break;
                case 'h':
                case 'a':
                    main_core->move_hero(Direction::Down);
                    break;
                case ' ':
                    main_core->wait();
                    break;
            }
            play_win->refresh_window();
            stat_win->refresh_window();
            log_win->refresh_window();
            chrs_win->refresh_window();
        }
    }

private:
    void init_windows() {
        stat_win    = std::make_shared<StatWindow>(sw_height, sw_width, 1, 1);
        play_win    = std::make_shared<PlayWindow>(pw_height, pw_width, sw_height + 3, 1);
        log_win     = std::make_shared<LogWindow>(lg_height, lg_width, sw_height + pw_height + 5, 1);
        chrs_win    = std::make_shared<ChrsWindow>(ch_height, ch_width, 1, sw_width + 3);
    }

private:
    std::shared_ptr<PlayWindow> play_win;
    std::shared_ptr<StatWindow> stat_win;
    std::shared_ptr<LogWindow>  log_win;
    std::shared_ptr<ChrsWindow> chrs_win;

private:
    const int pw_width   = 50;
    const int pw_height  = 20;
    const int sw_width   = 50;
    const int sw_height  = 3;
    const int lg_width   = 50;
    const int lg_height  = 4;
    const int ch_width   = 25;
    const int ch_height  = pw_height + sw_height + 2;
};
