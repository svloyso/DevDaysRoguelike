#pragma once
#include <iostream>
#include <unistd.h>
#include <vector>
#include <string>
#include <wstring>
#include <ncurses.h>

using namespace std;
 
class console_graphic
{
	int  width;
	int height;

public:
	console_graphic ();
	void print_wall ();
	void clear_screen ();
	void print_symbol (int pos_x, int pos_y, string symb_code);
	void draw_coin (int pos_x, int pos_y);
	~console_graphic ();

}