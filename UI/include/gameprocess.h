#ifndef GAMEPROCESS_H
#define GAMEPROCESS_H
#include "console_graphic.h"
#include "core.h"
#include <string>
class GameProcess
{
    ConsoleGraphics cons;

public:
    GameProcess();
    ~GameProcess();
    bool is_alive();
    void update(std::string str);
};

#endif // GAMEPROCESS_H
