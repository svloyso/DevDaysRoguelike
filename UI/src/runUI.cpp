#include <iostream>
#include <unistd.h>
#include <ncurses.h>
#include <cstdlib>
#include "runUI.h"

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
	
    GameProcess game;
    system ("stty raw");
    char input_char;
    while (1)
    {
        cout << "\033[0;0H";
		cout << "\033[30m" << "\033[0m" ;
        input_char = getchar();
        cout << "\033[1D" << "\033[30m" << " ";
        if (input_char == 'q' || !game.is_alive())
        {
            system ("stty cooked");
            break;
        }
        game.update (input_char);
        
        system("stty raw");

    }
    system ("clear");
    return 0;

}



