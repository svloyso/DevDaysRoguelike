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
		cout << "\033[30m" << "033[0m";
        input_char = getchar();
        cout << "\033[2С" << "\033[00m" << "\033[30m" << " ";
        if (input_char == 'q')
        {
            system ("stty cooked");
            break;
        }
        game.update (input_char);
        //cout << "\033[2D" << " ";
        system("stty raw");
    }

    return 0;

}



