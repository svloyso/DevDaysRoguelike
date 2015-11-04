#include "console_graphic.h"

ConsoleGraphics::ConsoleGraphics ()
    : core_mock ("map.txt")
{
    initscr();

    getmaxyx (stdscr, console_size_y, console_size_x);
    endwin();
    shift = 6;
    width = 16;
    height = 70;  // смещение по у
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

void ConsoleGraphics::clear_screen ()
{
    cout << "\033[2J";
}
void ConsoleGraphics::draw_coin (Coord x)
{
    print_symbol (x, "\u26C0", 15);
}
void ConsoleGraphics::print_symbol (Coord x, string symb_code, int color, int bg_color)
{
    cout << "\033[" << x.x << ";" << x.y << "H" << "\033[" << color << "m"<< symb_code<< "\033[00m";
}
void ConsoleGraphics::print_string (Coord x, string str, int color)
{
    cout << "\033[" << x.x << ";" << x.y << "H" << "\033[" << color << "m"<< str << "\033[00m";
}
void ConsoleGraphics::draw_hero ()
{
    Coord hero_pos_in_window (width / 2,  height / 2 );
    draw_in_window (hero_pos_in_window, "\uC720", 35);
}
void ConsoleGraphics::draw_hp_line (int max_hp, int cur_hp)
{
    if (cur_hp == max_hp)
    {
        cout << "\033[4;8H" << "|";
        cout << "\033[42m" << "    "<<  "\033[00m" << "|";
        cout << "\033[42m" << "    "<<  "\033[00m" << "|";
        cout << "\033[42m" << "    "<<  "\033[00m" << "|";
        cout << "\033[42m" << "    "<<  "\033[00m" << "|";
        cout << "\033[42m" << "    "<<  "\033[00m" << "|";
    }
}

void ConsoleGraphics::draw_hero_stats ()
{
    Coord x (2, 4);
    print_string (x, "HERO", 35);
    x = Coord (4, 4);
    print_string (x, "               ", 35);
    x = Coord (4, 4);
    print_string (x, "HP: ", 15);
    x = Coord (4, 7);
    cout << "400/400";
    draw_hp_line (400,400);
    // printf("%i / %i", unitsData[heroIndex].health, GetUnitDefaultHealth(UnitType_Hero));

    // SetConsoleCursorPosition(consoleHandle, cursor_coord);
    // SetConsoleTextAttribute(consoleHandle, ConsoleColor_Gray);
    // for (int i = 1; i <= GetUnitDefaultHealth(UnitType_Hero) / 20; i++)
    // {
    //     printf("%c", 219);
    //     if (i % 5 == 0)
    //         printf("%c", 179);
    // }

    // cursor_coord = { 11, 8 };
    // SetConsoleCursorPosition(consoleHandle, cursor_coord);
    // SetConsoleTextAttribute(consoleHandle, ConsoleColor_Red);
    // for (int i = 1; i <= unitsData[heroIndex].health / 20; i++)
    // {
    //     printf("%c", 219);
    //     if (i % 5 == 0)
    //         printf("%c", 179);
    // }
}
void ConsoleGraphics::draw_in_window (Coord x, string symb_code, int color, int bg_color)
{
    print_symbol (Coord(x.x + shift + 1, x.y + 2), symb_code, color, bg_color);
}

void ConsoleGraphics::refresh ()
{
    //Coord hero_pos (10,10);
    int x_left  = round (hero_pos.x - width / 2);
    int x_right = round (hero_pos.x + width / 2);
    int y_left  = round (hero_pos.y - height / 2);
    int y_right = round (hero_pos.y + height / 2);

    for (int j = x_left;  j < x_right ; ++j)
    {
        for (int i = y_left; i < y_right; ++i)
        {
            char obj_pos = core_mock.get_tile (Coord (j, i));
            switch(obj_pos)
            {
            case '#':
                draw_in_window (Coord (j - x_left, i - y_left), "0", 15);
                break;
            case ' ':
                print_symbol (Coord (j - x_left , i - y_left), " ", 15);
                break;
            }
        }
    }
    draw_hero();
    draw_wall();
    draw_hero_stats();
}
void ConsoleGraphics::move_hero_rigth ()
{
    core_mock.set_hero (Coord (hero_pos.x, hero_pos.y + 1));
    refresh();
}

ConsoleGraphics::~ConsoleGraphics ()
{}
