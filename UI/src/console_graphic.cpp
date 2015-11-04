#include "console_graphic.h"

ConsoleGraphics::ConsoleGraphics ()
    : hero_pos (0,0)
{
    initscr();
    getmaxyx (stdscr, console_size_y, console_size_x);
    endwin();

    shift = 8;
    width = 10;
    height = 70;  // смещение по у
    refresh();
}
void ConsoleGraphics::init()
{
    core->set_hero (Coord (0, 0));
    initscr();
    getmaxyx (stdscr, console_size_y, console_size_x);
    endwin();

    shift = 6;
    width = 10;
    height = 70;  // смещение по у
    refresh();
}
void ConsoleGraphics::draw_wall ()
{
    //cout << "\033[2J";
    for (int i = 1; i <= height + 2; i++)
    {
        print_symbol(Coord(shift, i), "\u2501", 15);               // -
        print_symbol(Coord(width  +  shift + 1, i), "\u2501", 15);
    }
    for (int i = shift; i <= width + shift; i++)
    {
        print_symbol(Coord(i, 0), "\u2503", 15);               // |
        print_symbol(Coord(i + 1, height + 2), "\u2503", 15);
    }

    print_symbol (Coord(shift, 0), "\u250F", 15);           // левый верхний угол
    print_symbol (Coord(width  + shift + 1, 0), "\u2517", 15);     //левый нижний угол
    print_symbol (Coord(width  + shift + 1, height + 2), "\u251B", 15);    // ┛
    print_symbol (Coord(shift, height + 2), "\u2513", 15);  //правый верхний угол
}

void ConsoleGraphics::draw_coin (Coord x)
{
    print_symbol (x, "\u26C0", 14);
}

void ConsoleGraphics::draw_hero ()
{
    Coord hero_pos_in_window (width / 2,  height / 2 );
    draw_in_window (hero_pos_in_window, "\uC720", 35);
}

void ConsoleGraphics::draw_in_window (Coord x, string symb_code, int color, int bg_color)
{
    print_symbol (Coord(x.x + shift + 1, x.y + 2), symb_code, color, bg_color);
}

void ConsoleGraphics::refresh ()
{
    hero_pos = core->get_hero();
    int x_left  = hero_pos.x - width / 2;
    int x_right = hero_pos.x + width / 2;
    int y_left  = hero_pos.y - height / 2;
    int y_right = hero_pos.y + height / 2;

    for (int j = x_left;  j < x_right ; ++j)
    {
        for (int i = y_left; i < y_right; ++i)
        {
            TilePtr tile = core->get_tile (Coord (j, i));
			std::string str;
			if( tile->get_type() == TileType::Wall ) {
                str = "#";
            } 
            if ( tile->get_type() == TileType::Floor ) {
                if (tile->get_immovables().size()) {
                    str = "D";
                } else {
                    str = ".";
                }
            }
			draw_in_window (Coord (j - x_left, i - y_left), str, 15);
/*
            switch(obj_pos)
            {
            case '#':
                draw_in_window (Coord (j - x_left, i - y_left), "0", 15);
                break;
            case ' ':
                draw_in_window (Coord (j - x_left , i - y_left), " ", 15);
                break;
//            case 'x':
//                print_symbol (Coord (j - x_left , i - y_left), "x", 15);
//                break;
            }
*/
        }
    }
    draw_hero();
    draw_wall();
    info.draw_hero_stats();

    //set_cursor_in_win_center();
}
void ConsoleGraphics::move_hero_right ()
{
    core->set_hero (Coord (hero_pos.x, hero_pos.y + 1));
    refresh();
}
void ConsoleGraphics::move_hero_left ()
{
    core->set_hero (Coord (hero_pos.x, hero_pos.y - 1));
    refresh();
}
void ConsoleGraphics::move_hero_up ()
{
    core->set_hero (Coord (hero_pos.x - 1, hero_pos.y));
    refresh();
}
void ConsoleGraphics::move_hero_down ()
{
    core->set_hero (Coord (hero_pos.x + 1, hero_pos.y));
    refresh();
}
ConsoleGraphics::~ConsoleGraphics ()
{}
