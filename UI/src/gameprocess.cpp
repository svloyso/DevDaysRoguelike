#include "gameprocess.h"

GameProcess::GameProcess()
{}
void GameProcess::update (char input_char)
{
    switch (input_char)
    {
    case 'd':
        cons.move_hero_down();
        cout << "\033[" << "0"  << ";" << "0" << "H"<< "\033[30m" << "\033[0m";
        break;
    case 's':
        cons.move_hero_left();
        cout << "\033["<< "0"  << ";" << "0" << "H" << "\033[30m" << "\033[0m";
        break;
    case 'a':
        cons.move_hero_up();
        cout << "\033[" << "0"  << ";" << "0" << "H" << "\033[30m" << "\033[0m";
        break;
    case 'w':
        cons.move_hero_right();
        cout << "\033[" << "0"  << ";" << "0" << "H" << "\033[30m" << "\033[0m";
        break;
    case 'r':
        cons.init();
        break;
//    case 'e':
//        isGameActive = false;
//        break;
    default:
        cout << "\033[0;0H" << "\033[30m" << "\033[0m";
    }

//    if (unitsData[heroIndex].health <= 0)
//        isGameActive = false;
//    else if (unitsData[heroIndex].health < GetUnitDefaultHealth(UnitType_Hero))
//        unitsData[heroIndex].health++;
}
GameProcess::~GameProcess()
{
    cout << "\033[00m" << "Код 00\n"<< "\033[00m";
}
bool GameProcess::is_alive()
{
    if (cons.is_alive())
    {
        return true;
    }
    system ("clear");
    cout << "GAME OVER!";
    return false;
}
