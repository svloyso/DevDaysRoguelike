#ifndef CONSOLEPRINT
#define CONSOLEPRINT
#include <unistd.h>
#include <string>
#include <ncurses.h>
#include "core.h"
#include "utils.h"

void clear_screen ();
void print_symbol (Coord x, std::string symb_code, int color, int bg_color = 30);
void print_string (Coord x, std::string str, int color);
void set_cursor_in_win_center ();

#endif // CONSOLEPRINT

