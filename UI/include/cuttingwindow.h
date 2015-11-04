#ifndef CUTTINGWINDOW_H
#define CUTTINGWINDOW_H
#include "consoleprint.h"
#include <unistd.h>
#include <string>
#include <ncurses.h>
#include "utils.h"
using namespace  std;

class CuttingWindow
{
    Coord left_up;
    Coord right_bot;

public:
    CuttingWindow (Coord _left_up, Coord _right_bot);
    void print (Coord x, string str, int color, int bg = 15);
    void get_size (int &x, int &y);
};

#endif // CUTTINGWINDOW_H

