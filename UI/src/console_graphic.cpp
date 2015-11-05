#include "console_graphic.h"
#include "myvisitor.h"

ConsoleGraphics::ConsoleGraphics()
    : game_play_point (Coord (9, 1))
    , game_play (CuttingWindow (game_play_point, Coord (20, 48)))
    , stats_point (Coord (1,1))
    , stats_window (CuttingWindow (stats_point, Coord (5, 80)))
    , info (stats_window)
    , invent_point (Coord (9, 52))
    , invent_window (CuttingWindow (invent_point, Coord (20, 80)))
{
    stats_window.get_size (stats_width, stats_height);
    game_play.get_size (game_play_width, game_play_height);
    invent_window.get_size (invent_width, invent_height);
    init();

}

void ConsoleGraphics::init()
{
    initscr ();
    getmaxyx (stdscr, console_size_y, console_size_x);
    endwin ();
    refresh ();
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

void ConsoleGraphics::draw_hero ( )
{
    game_play.print(Coord (game_play_width / 2, game_play_height / 2), "\u2689", 33);
}
bool ConsoleGraphics::is_alive()
{
    HeroPtr hero = main_core->get_hero();
    HeroStats * hero_stats = hero->get_stats();
    int hero_hp = hero_stats->hit_points;
    if (hero_hp <= 0 )
    {
        return false; 
    }
    return true;
}

void ConsoleGraphics::refresh ()
{
	cout << "\033[2J";

	Coord hero_pos;
    HeroPtr hero = main_core->get_hero();
    hero_pos = main_core->get_coord (hero->get_pos());
    
    HeroStats * hero_stats = hero->get_stats();
    int hero_hp = hero_stats->hit_points;
    int hero_maxhp = hero_stats->max_hit_points;
    
    info.hero_draw_stats (hero_hp, hero_maxhp);
    draw_wall (Coord (stats_point.x , stats_point.y ),
        stats_height + 2, stats_width + 2);
    MyVisitor visitor;
    int x_left  = hero_pos.x - game_play_width / 2;
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

    UnitPtr unit = main_core->get_enemy();
            if (unit) 
            {
                UnitStats * stats = unit->get_stats();
                int hp = stats->hit_points;
                int max_hp = stats->max_hit_points;
                if (hp > 0) 
                {
                    info.enemy_draw_stats (hp, max_hp, "ENEMY");
                }
                else 
                {
                    info.clear_enemy_info();
                }
            }
    draw_wall( Coord (game_play_point.x - 1, game_play_point.y - 1), 
        game_play_height + 2, game_play_width + 2);
    draw_wall( Coord (invent_point.x - 1, invent_point.y - 1), 
        invent_height + 2, invent_width + 2);
    draw_hero ();
    invent_window.print (Coord (1,1), "Up:    w | k", 15);
    invent_window.print (Coord (3,1), "Down:  s | j", 15);
    invent_window.print (Coord (5,1), "Right: d | l", 15);
    invent_window.print (Coord (7,1), "Left:  a | h", 15);
    invent_window.print (Coord (9,1), "Quit:  q ", 15);
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
