#include "consoleprint.h"
void clear_screen ()
{
    std::cout << "\033[2J";
}
void print_symbol (Coord x, std::string symb_code, int color, int bg_color)
{
    std::cout << "\033[" << x.x << ";" << x.y << "H" << "\033[" << color << "m"<< symb_code<< "\033[00m";
}
void print_string (Coord x, std::string str, int color)
{
    std::cout << "\033[" << x.x << ";" << x.y << "H" << "\033[" << color << "m"<< str << "\033[00m";
}

