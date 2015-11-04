#include "cuttingwindow.h"

CuttingWindow::CuttingWindow (Coord _left_up, Coord _right_bot)
    : left_up   (_left_up)
    , right_bot (_right_bot)
{}

void CuttingWindow::print (Coord x, string str, int color, int bg)
{
    Coord new_x = Coord (left_up.x + x.x, left_up.y + x.y);
    print_symbol (new_x, str, color, bg);
}
void CuttingWindow::get_size (int &  x, int & y)
{
    x = right_bot.x  - left_up.x + 1;
    y = right_bot.y  - left_up.y + 1 ;
}

