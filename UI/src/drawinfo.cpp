#include "drawinfo.h"

DrawInfo::DrawInfo(int _hero_max_hp, int _hero_cur_hp)
    : hero_max_hp (_hero_max_hp)
    , hero_cur_hp (_hero_cur_hp)
{
}

void DrawInfo::draw_hp()
{
    Coord x (2, 4);
    print_string (x, "HERO", 35);
    x = Coord (4, 4);
    print_string (x, "               ", 35);
    x = Coord (4, 4);
    print_string (x, "HP: ", 15);
    x = Coord (4, 7);
    cout << hero_cur_hp << "/" << hero_max_hp;
}
void DrawInfo::draw_hero_stats (int _hero_cur_hp)
{
    draw_empty_hp_line ();
    hero_cur_hp = _hero_cur_hp;
    norma = hero_cur_hp / hero_max_hp;
    compute_diff ();
    if (norma == 1)
    {
        draw_hp ();
        draw_full_hp_line ();
        return;
    }
    if (norma >= 0.8)
    {
        draw_hp ();
        draw_green_hp_line ();
        return;
    }
//    if (norma >= 0.4)
//    {
//        draw_mid_hp();
//        draw_mid_hp_line();
//      void DrawInfo::draw_empty_hp_line ()
    {
            cout << "\033[6;4H" << "|";
            cout << "    "<<  "\033[00m" << "|";
            cout << "    "<<  "\033[00m" << "|";
            cout << "    "<<  "\033[00m" << "|";
            cout << "    "<<  "\033[00m" << "|";
            cout << "    "<<  "\033[00m" << "|";

    }  return;
//    }
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
void DrawInfo::draw_empty_hp_line ()
{
        cout << "\033[6;4H" << "|" <<  "\033[00m";
        cout << "    "<<  "\033[00m" << "|";
        cout << "    "<<  "\033[00m" << "|";
        cout << "    "<<  "\033[00m" << "|";
        cout << "    "<<  "\033[00m" << "|";
        cout << "    "<<  "\033[00m" << "|";

}
void DrawInfo::draw_full_hp_line ()
{

        cout << "\033[6;4H" << "|";
        cout << "\033[42m" << "    "<<  "\033[00m" << "|";
        cout << "\033[42m" << "    "<<  "\033[00m" << "|";
        cout << "\033[42m" << "    "<<  "\033[00m" << "|";
        cout << "\033[42m" << "    "<<  "\033[00m" << "|";
        cout << "\033[42m" << "    "<<  "\033[00m" << "|";
}
void DrawInfo::draw_green_hp_line ()
{
    cout << "\033[4;8H" << "|";
    cout << "\033[42m" << "    "<<  "\033[00m" << "|";
    cout << "\033[42m" << "    "<<  "\033[00m" << "|";
    cout << "\033[42m" << "    "<<  "\033[00m" << "|";
    cout << "\033[42m" << "    "<<  "\033[00m" << "|";
    draw_one_part(42);
}
void DrawInfo::draw_one_part (int color)
{
    cout << "\033[" << color << "m";
    for (int i = 0; i < fractions_count; ++i)
    {
        cout  << " ";
    }
    cout << "\033[00m";
    for (int i = 0; i < 5 - fractions_count; --i)
    {
        cout << " ";
    }
    cout << "|";
}

int DrawInfo::compute_diff ()
{
    one_part_hp = hero_max_hp / 5;
    full_parts_count = hero_cur_hp / one_part_hp;
    fractions_count = (hero_cur_hp - full_parts_count * one_part_hp ) % 5;
}
