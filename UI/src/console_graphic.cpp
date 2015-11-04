#include "console_graphic.h"
#include "core.h"

ConsoleGraphics::ConsoleGraphics ()
    : hero_pos (0,0)
{
    initscr();
    getmaxyx (stdscr, console_size_y, console_size_x);
    endwin();

    shift = 8;
    width = 16;
    height = 70;  // смещение по у
    refresh();

	codes["1111"] = "\u253C";
	codes["1110"] = "\u2534";
	codes["1101"] ="\u2524";
	codes["0111"] ="\u251C";
	codes["1011"] = "\u252C";
	codes["0101"] ="\u2502";
	codes["1010"] ="\u2500";
	codes["1100"]= "\u2518";
	codes["0110"] ="\u2514";
	codes["0011"] ="\u250C";
	codes["1001"] ="\u2510";
	codes["0100"] ="\u2575";
	codes["0010"] ="\u2576";
	codes["0001"] ="\u2577";
	codes["1000"] ="\u2574";
	codes["0000"] =" ";
}
void ConsoleGraphics::init()
{
    main_core->set_hero (Coord (0, 0));
    initscr();
    getmaxyx (stdscr, console_size_y, console_size_x);
    endwin();

    shift = 8;
    width = 16;
    height = 70;  // смещение по у
    refresh();
}

string ConsoleGraphics::GetRenderCellSymbolWall(int r, int c)
{
    string code = "";

    if ((main_core->get_tile (Coord (r, c-1)))->get_type() == TileType::Wall)
    	code += "1";
    else
    	code += "0";

    if ((main_core->get_tile (Coord (r-1, c)))->get_type() == TileType::Wall)
    	code += "1";
    else
    	code += "0";

    if ((main_core->get_tile (Coord (r, c+1)))->get_type() == TileType::Wall)
    	code += "1";
    else
    	code += "0";

    if ((main_core->get_tile (Coord (r+1, c)))->get_type() == TileType::Wall)
    	code += "1";
    else
    	code += "0";

	return codes[code];
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
    print_symbol (x, "\u26C0", 14, 30);
}

void ConsoleGraphics::draw_hero ()
{
    Coord hero_pos_in_window (width / 2,  height / 2 );
    draw_in_window (hero_pos_in_window, "\uC720", 31);
}

void ConsoleGraphics::draw_in_window  (Coord x, string symb_code, int color)
{
    print_symbol (Coord (x.x + shift + 1, x.y + 2), symb_code, color);
}
void ConsoleGraphics::draw_door (Coord x)
{
	draw_in_window (x, "\u2592", 14);
}
void ConsoleGraphics::refresh ()
{
	cout << "\033[2J";
    hero_pos = main_core->get_hero();
    int x_left  = hero_pos.x - width / 2;
    int x_right = hero_pos.x + width / 2;
    int y_left  = hero_pos.y - height / 2;
    int y_right = hero_pos.y + height / 2;

    for (int j = x_left;  j < x_right ; ++j)
    {
        for (int i = y_left; i < y_right; ++i)
        {
            TilePtr tile = main_core->get_tile (Coord (j, i));
			std::string str;
			if( tile->get_type() == TileType::Wall ) 
			{
                str = GetRenderCellSymbolWall(j, i);
                draw_in_window (Coord (j - x_left, i - y_left), str, 15);
                continue;
            } 
			else if ( tile->get_type() == TileType::Floor ) 
			{
                if (tile->get_immovables().size()) 
				{
                   str = "D";
                    continue;
                } 
				else 
				{
                    str = " ";
                }
            } 
			else {
				str = 'x';
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
    main_core->set_hero (Coord (hero_pos.x, hero_pos.y + 1));
    refresh();
}
void ConsoleGraphics::move_hero_left ()
{
    main_core->set_hero (Coord (hero_pos.x, hero_pos.y - 1));
    refresh();
}
void ConsoleGraphics::move_hero_up ()
{
    main_core->set_hero (Coord (hero_pos.x - 1, hero_pos.y));
    refresh();
}
void ConsoleGraphics::move_hero_down ()
{
    main_core->set_hero (Coord (hero_pos.x + 1, hero_pos.y));
    refresh();
}
ConsoleGraphics::~ConsoleGraphics ()
{}
