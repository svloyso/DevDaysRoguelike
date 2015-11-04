#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include <iostream>
#include <string>
 
 #define TILE_FLOOR 0
 #define TILE_WALL 1
 #define TILE_POINT 2
 #define TILE_DOOR 3
  
 int **grid;

using namespace std;

int size_x;
int size_y;

const int numDoor = 7;
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