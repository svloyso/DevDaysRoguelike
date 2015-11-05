#ifndef GAMEPROCESS_H
#define GAMEPROCESS_H
#include "console_graphic.h"
#include "core.h"
class GameProcess
{
    ConsoleGraphics cons;

public:
    GameProcess();
    ~GameProcess();
    bool is_alive();
    void update(char input_char);
};

#endif // GAMEPROCESS_H
