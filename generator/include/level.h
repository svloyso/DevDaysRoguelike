#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "levelParams.h"

#include "core.h"
#include "tile.h"
#include "door.h"
 
 #define TILE_FLOOR 0
 #define TILE_WALL 1
 #define TILE_POINT 2
 #define TILE_DOOR 3
 #define TILE_EXIT 4

using namespace std;

vector< vector<int> > grid;

int numDoor = (size_x / size_room_x) * (size_y / size_room_y) - 1;
int *rowDoor = new int[numDoor];
int *columnDoor = new int[numDoor];	
void GenerateStuff(int *rowStuff, int *columnStuff);

bool exploreMatr(int from, int to, bool* visited);
void Generate();
void ClearField();
void genRoom(int row, int column, int door);
void genRooms();
void initmap(void);
string GetRenderCellSymbolWall(int r, int c);
void printmap(void);
