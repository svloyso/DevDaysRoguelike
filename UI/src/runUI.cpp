#include <iostream>
#include <unistd.h>
#include <ncurses.h>
#include <cstdlib>
#include "runUI.h"
#include <string>
#include "gameprocess.h"
using namespace std;
// void recv_action(ActionPtr action) {
// 	switch(action->get_type()) {
// 		case ActionType::Move:
// 			if (action->get_action()->get_id() == hero_id)
// 				repaint();
// 	}
// }
int runUI()
{
    system("setterm -cursor off");
	
    GameProcess game;
    system ("stty raw");
    std::string str;
    while (1)
    {
        if (!game.is_alive())
        {
            str = getchar();
            if (str == "r")
            {
                game.update (str);
            }
        }
        cout << "\033[0;0H";
		cout << "\033[30m" << "\033[0m" ;
        str = getchar();
        cout << "\033[1D" << "\033[30m" << " ";
        if (str == "q")
        {
            system ("stty cooked");
            break;
        }
        game.update (str);
        
        system("stty raw");

    }
    
    system("setterm -cursor on");
    system ("clear");
    return 0;

}



