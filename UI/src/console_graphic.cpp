#include "console_graphic.h"
#include "myvisitor.h"

ConsoleGraphics::ConsoleGraphics()
    : game_play_point (Coord (9, 1))
    , game_play (CuttingWindow (game_play_point, Coord (20, 60)))
{
    initscr ();
    getmaxyx (stdscr, console_size_y, console_size_x);
    endwin ();

    game_play.get_size (game_play_width, game_play_height);
    refresh ();
}

void ConsoleGraphics::init()
{
    initscr();
    getmaxyx (stdscr, console_size_y, console_size_x);
    endwin();

    shift = 8;
    width = 16;
    height = 70;  // смещение по у
    refresh();
}

string ConsoleGraphics::get_render_cell_symbol_wall (int r, int c)
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
void ConsoleGraphics::draw_wall (Coord c, int h, int w)
{
    for (int i = c.y; i < c.y + h; ++i)
    {
        print_string(Coord (c.x, i), "\u2501", 15);               // -
        print_string(Coord (w + c.x - 1, i), "\u2501", 15);
    }
    for (int i = c.x; i < w + c.x; ++i)
    {
        print_string(Coord (i, c.y), "\u2503", 15);               // |
        print_string(Coord (i, c.y + h - 1), "\u2503", 15);
    }

    print_string (c, "\u250F", 15);           // левый верхний угол
    print_string (Coord (w  + c.x - 1, c.y), "\u2517", 15);     //левый нижний угол
    print_string (Coord (w  + c.x - 1, h + c.y - 1), "\u251B", 15);    // ┛
    print_string (Coord (c.x, h + c.y - 1), "\u2513", 15);  //правый верхний угол
} 

void ConsoleGraphics::draw_coin (Coord x)
{
    print_symbol (x, "\u26C0", 14, 30);
}

void ConsoleGraphics::refresh ()
{
	cout << "\033[2J";
	Coord hero_pos;
    HeroPtr hero = main_core->get_hero();
    hero_pos = main_core->get_coord(hero->get_pos());
    MyVisitor visitor;
    int x_left  = hero_pos.x -game_play_width / 2;
    int x_right = hero_pos.x + game_play_width / 2;
    int y_left  = hero_pos.y - game_play_height / 2;
    int y_right = hero_pos.y + game_play_height / 2;

    for (int j = x_left;  j < x_right ; ++j)
    {
        for (int i = y_left; i < y_right; ++i)
        {
            TilePtr tile = main_core->get_tile (Coord (j, i));
            visitor.visit(tile);
            game_play.print (Coord (j - x_left, i - y_left), visitor.get_val(), visitor.get_color());
        }
    }
    draw_wall( Coord (game_play_point.x - 1, game_play_point.y - 1), 
        game_play_height + 2, game_play_width + 2);
    info.draw_hero_stats();
    //set_cursor_in_win_center();
}
void ConsoleGraphics::move_hero_right ()
{
    main_core->move_hero(Direction::Left);
    refresh();
}
void ConsoleGraphics::move_hero_left ()
{
    main_core->move_hero(Direction::Right);
    refresh();
}
void ConsoleGraphics::move_hero_up ()
{
    main_core->move_hero(Direction::Down);
    refresh();
}
void ConsoleGraphics::move_hero_down ()
{
    main_core->move_hero(Direction::Up);
    refresh();
}
ConsoleGraphics::~ConsoleGraphics ()
{}
