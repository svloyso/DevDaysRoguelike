#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "levelParams.h"

//#include "core.h"
//#include "tile.h"
//#include "door.h"
 
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


enum itemType
{
	weapon,
	head,
	body,
	arms,
	legs
};

enum statType
{
	health,
	strength
};

struct Item
{
	itemType type;
	statType stat;
	int effect;
};

struct Fraction
{
	int name;
	int health;
	int strength;
	int probability;
};

struct Mob
{
	int fraction;
	int health;
	int strength;	
	vector< Item > inventory;
	int x;
	int y;
};

vector<Mob> mobs;
vector<Fraction> fraction(numFractions);
vector<Item> stuff;

bool fractPower(Fraction i, Fraction j);
void genFraction();
Mob genMob(Fraction fract);
void genItems();
