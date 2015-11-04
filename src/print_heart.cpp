#include <iostream>
#include <unistd.h>
#include <ncurses.h>
#include <cstdlib>

#include "gameprocess.h"
using namespace std;
// void recv_action(ActionPtr action) {
//  switch(action->get_type()) {
//      case ActionType::Move:
//          if (action->get_action()->get_id() == hero_id)
//              repaint();
//  }
// }
int main()
{
    GameProcess game;
    system("stty raw");
    char input_char;
    while (1)
    {
        input_char = getchar();
        cout << "\033[1D" << " ";
        if (input_char == 'q')
        {
            system ("stty cooked");
            break;
        }
        game.update (input_char);
        cout << "\033[1D" << " ";
        system("stty raw");
    }

    return 0;
}


