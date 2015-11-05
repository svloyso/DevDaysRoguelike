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
#include "monster.h"
#include "stats.h"
#include "AI.h"
 
 #define TILE_FLOOR 0
 #define TILE_WALL 1
 #define TILE_POINT 2
 #define TILE_DOOR 3
 #define TILE_EXIT 4

 #define TILE_ORC 5
 #define TILE_SKELETON 6

using namespace std;

vector< vector<int> > grid;

int numDoor = (size_x / size_room_x) * (size_y / size_room_y) - 1;
int *rowDoor = new int[numDoor];
int *columnDoor = new int[numDoor];	
void GenerateStuff(int *rowStuff, int *columnStuff);
bool GenerateMobs(int from, int to, bool* visited);

bool exploreMatr(int from, int to, bool* visited);
void Generate();
void ClearField();
void genRoom(int row, int column, int door);
void genRooms();
void initmap(void);
string GetRenderCellSymbolWall(int r, int c);
void printmap(void);


enum MyItemType
{
	weapon,
	head,
	body,
	arms,
	legs
};

enum MystatType
{
	health,
	strength
};

struct MyItem
{
	MyItemType type;
	MystatType stat;
	int effect;
};

struct MyFraction
{
	int name;
	int health;
	int strength;
	int probability;
};

struct MyMob
{
	int fraction;
	int health;
	int strength;	
	vector< MyItem > inventory;
	int x;
	int y;
};

vector<MyMob> mobs;
vector<MyFraction> fraction(numFractions);
vector<MyItem> stuff;

vector< vector<MyMob> > gridMob(size_y+3, vector<MyMob>(size_x+3));

bool fractPower(MyFraction i, MyFraction j);
void genFraction();
MyMob genMob(MyFraction fract);
void genItems();