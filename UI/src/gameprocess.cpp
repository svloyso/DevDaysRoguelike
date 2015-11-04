#include "gameprocess.h"

GameProcess::GameProcess()
{}
void GameProcess::update (char input_char)
{
    switch (input_char)
    {
    case 'd':
        cons.move_hero_right();
        cout << "\033[" << "50"  << ";" << "80" << "H"<< "\033[30m" << "\033[0m";
        break;
    case 's':
        cons.move_hero_down();
        cout << "\033["<< "50"  << ";" << "80" << "H" << "\033[30m" << "\033[0m";
        break;
    case 'a':
        cons.move_hero_left();
        cout << "\033[" << "50"  << ";" << "80" << "H" << "\033[30m" << "\033[0m";
        break;
    case 'w':
        cons.move_hero_up();
        cout << "\033[" << "50"  << ";" << "80" << "H" << "\033[30m" << "\033[0m";
        break;
    case 'r':
        cons.init();
        break;
//    case 'e':
//        isGameActive = false;
//        break;
    default:
        cout << "\033[50;80H" << "\033[30m" << "\033[0m";
    }

//    if (unitsData[heroIndex].health <= 0)
//        isGameActive = false;
//    else if (unitsData[heroIndex].health < GetUnitDefaultHealth(UnitType_Hero))
//        unitsData[heroIndex].health++;
}

