#include "console_graphic.h"

console_graphic::console_graphic ()
{
	initscr();
    int maxx, maxy = 0;
    getmaxyx (stdscr, maxx, maxy);
    endwin();
    int height = maxy - 1;
    int width = maxx - 1;
}

void console_graphic::print_wall ()
{

	cout << "\033[2J";
    for (int i = 2; i <= height; i++)
    {
        print_symbol(i, 0, "\u2501");               // -
        print_symbol(i, width, "\u2501");
    }
    for (int i = 2; i < width; i++)
    {
        print_symbol(0, i, "\u2503");               // |
        print_symbol(height + 1, i, "\u2503");
    }
    print_symbol(0, 0, "\u250F");    // левый верхний угол 
    print_symbol (height + 1, 0, "\u2513"); //правый верхний угол
    print_symbol (height + 1, width, "\u251B");    // ┛
    print_symbol (0, width, "\u2517"); //левый нижний угол

}

void console_graphic::clear_screen ()
{
	cout << "\033[2J";
}
void console_graphic::draw_coin (int pos_x, int pos_y)
{
	print_symbol (pos_x, pos_y, "\u26C0");
}
void console_graphic::print_symbol (int pos_x, int pos_y, string symb_code)
{
	cout << "\033[" << pos_x << ";" << pos_y << "H" << symb_code;
}
console_graphic::~console_graphic ()
{}