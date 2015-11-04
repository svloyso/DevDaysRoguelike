#ifndef GAMEPROCESS_H
#define GAMEPROCESS_H
#include "console_graphic.h"

class GameProcess
{
    ConsoleGraphics cons;

public:
    GameProcess();
    void update(char input_char);
};

#endif // GAMEPROCESS_H
