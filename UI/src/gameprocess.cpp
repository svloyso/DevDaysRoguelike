#include "gameprocess.h"

GameProcess::GameProcess()
{}
void GameProcess::update (std::string s)
{
    if (s == "l" || s ==  "\033[1C" || s ==  "d" )
    {
        cons.move_hero_down();
        cout << "\033[" << "0"  << ";" << "0" << "H"<< "\033[30m" << "\033[0m";
            return;
    }
    if (s == "s" || s ==  "j"  )
     {
        cons.move_hero_left();
        cout << "\033["<< "0"  << ";" << "0" << "H" << "\033[30m" << "\033[0m";
        return;
     }
    if (s == "a" || s==  "h" )
    {
        cons.move_hero_up();
        cout << "\033[" << "0"  << ";" << "0" << "H" << "\033[30m" << "\033[0m";
        return;
    }
    if (s== "w" || s==  "k" || s ==  "\033[1A" )
    {
        cons.move_hero_right();
        cout << "\033[" << "0"  << ";" << "0" << "H" << "\033[30m" << "\033[0m";
        return;
    }
    if (s == "r")
    {
        cons.init();
        cout << "\033[" << "0"  << ";" << "0" << "H" << "\033[30m" << "\033[0m";
        return;
    }
        cout << "\033[0;0H" << "\033[30m" << "\033[0m";


//    if (unitsData[heroIndex].health <= 0)
//        isGameActive = false;
//    else if (unitsData[heroIndex].health < GetUnitDefaultHealth(UnitType_Hero))
//        unitsData[heroIndex].health++;
}
GameProcess::~GameProcess()
{
    cout << "\033[00m" <<  "\033[00m";
}
bool GameProcess::is_alive()
{
    if (cons.is_alive())
    {
        return true;
    }
    //system ("clear");
    //cout << "GAME OVER!";
    return false;
}
