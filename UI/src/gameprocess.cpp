#include "gameprocess.h"

GameProcess::GameProcess()
{}
void GameProcess::update (char input_char)
{
    switch (input_char)
    {
    case 'd':
        cons.move_hero_right();
        break;
    case 's':
        cons.move_hero_down();
        break;
    case 'a':
        cons.move_hero_left();
        break;
    case 'w':
        cons.move_hero_up();
        break;
    case 'r':
        cons.init();
        break;
//    case 'e':
//        isGameActive = false;
//        break;
    }

//    if (unitsData[heroIndex].health <= 0)
//        isGameActive = false;
//    else if (unitsData[heroIndex].health < GetUnitDefaultHealth(UnitType_Hero))
//        unitsData[heroIndex].health++;
}

