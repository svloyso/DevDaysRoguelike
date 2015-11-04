#include "level.h"

bool exploreMatr(int from, int to, bool* visited)
{
	bool isGoodPath = false;

	visited[from] = true;

	if (from == to)
		return true;

	int r = from / size_x;
	int c = from % size_x;

	if ((r + 1 > 0) && (r + 1 < size_y))
		if ((grid[r + 1][c] != TILE_WALL) && (!visited[(r + 1) * size_x + c]))
			isGoodPath |= exploreMatr((r + 1) * size_x + c, to, visited);

	if ((r - 1 > 0) && (r - 1 < size_y))
		if ((grid[r - 1][c] != TILE_WALL) && (!visited[(r - 1) * size_x + c]))
			isGoodPath |= exploreMatr((r - 1) * size_x + c, to, visited);

	if ((c + 1 > 0) && (c + 1 < size_x))
		if ((grid[r][c + 1] != TILE_WALL) && (!visited[r * size_x + c + 1]))
			isGoodPath |= exploreMatr(r * size_x + c + 1, to, visited);

	if ((c - 1 > 0) && (c - 1 < size_x))
		if ((grid[r][c - 1] != TILE_WALL) && (!visited[r * size_x + c - 1]))
			isGoodPath |= exploreMatr(r * size_x + c - 1, to, visited);

	return isGoodPath;
}


void Generate()
{
	int num = size_y * size_x;
	bool *visited = new bool[num];

	//int *rowStuff = new int[numStuff];
	//int *columnStuff = new int[numStuff];	

	//GenerateStuff(rowStuff, columnStuff);

	int from = (size_y - 2) * size_x + 2;
	int to = size_x + size_x - 3; 

	
	for (int i = 0; i < (num / 10) * 5; i++)
	{
		int n = rand() % (size_y * size_x);
		int r = n / size_x;
		int c = n % size_x;

		if ((r > 1) && (r < size_y - 2) && (c > 1) && (c < size_x - 2))
			
			if (grid[r][c] == TILE_FLOOR)
			{
				grid[r][c] = TILE_WALL;

				for (int i = 0; i < num; i++)
					visited[i] = false;
				if (!exploreMatr(from, to, visited))
					grid[r][c] = TILE_FLOOR;

				for (int i = 0; i < numDoor; i++)
				{
					for (int j = 0; j < num; j++)
						visited[j] = false;
					if (!exploreMatr(rowDoor[i] * size_x + columnDoor[i], to, visited))
						grid[r][c] = TILE_FLOOR;
				}
			}
	}

	/*// Заполним недостижимые области
	for (int r = 0; r < size_y; r++)
	{
		for (int c = 0; c < size_x; c++)
		{
			for (int j = 0; j < num; j++)
				visited[j] = false;
			if (grid[r][c] == TILE_FLOOR)
				if (!exploreMatr(r * size_x + c, to, visited))
					grid[r][c] = TILE_FLOOR;
		}
	}*/
	
	for (int r = 2; r < size_y - 2; r++)
	{
		for (int c = 2; c < size_x - 2; c++)
		{
			if (grid[r][c] == TILE_FLOOR)
			{
				if (((grid[r + 1][c] == TILE_WALL) && (grid[r - 1][c] == TILE_WALL) && (grid[r][c + 1] == TILE_WALL) && (grid[r][c - 1] == TILE_WALL)) ||
					((grid[r + 1][c] != TILE_WALL) && (grid[r - 1][c] == TILE_WALL) && (grid[r][c + 1] == TILE_WALL) && (grid[r][c - 1] == TILE_WALL)) ||
					((grid[r + 1][c] == TILE_WALL) && (grid[r - 1][c] == TILE_WALL) && (grid[r][c + 1] != TILE_WALL) && (grid[r][c - 1] == TILE_WALL)) ||
					((grid[r + 1][c] == TILE_WALL) && (grid[r - 1][c] == TILE_WALL) && (grid[r][c + 1] == TILE_WALL) && (grid[r][c - 1] != TILE_WALL)) ||
					((grid[r + 1][c] == TILE_WALL) && (grid[r - 1][c] != TILE_WALL) && (grid[r][c + 1] == TILE_WALL) && (grid[r][c - 1] == TILE_WALL)))

					grid[r][c] = TILE_WALL;
			}
			else if (grid[r][c] == TILE_WALL)
				if ((grid[r + 1][c] != TILE_WALL) && (grid[r - 1][c] != TILE_WALL) && (grid[r][c + 1] != TILE_WALL) && (grid[r][c - 1] != TILE_WALL))
				grid[r][c] = TILE_FLOOR;
		}
	}

	
	//for (int i = 0; i < num; i++)
	//	visited[i] = false;
	//GenerateMobs(from, to, visited);

	return;
}

/*void GenerateStuff(int *rowStuff, int *columnStuff)
{
	unsigned char stuff[numStuff] = { '9', '9', '9', '9', '9', '9', '9' }; // Òèïà âåùè

	for (int i = 0; i < numStuff; i++)
		std::swap(stuff[i], stuff[rand() % 7]); // ïåðåìåøèâàåì

	// Ðàñêèäûâàåì âåùè; Äà, ýòî ãîâíîêîä
	rowStuff[0] = 2 + rand() % (size_y / 3);
	columnStuff[0] = 2 + (rand() % (size_x / 4));
	if (grid[rowStuff[0]][columnStuff[0]] == TILE_FLOOR)
		grid[rowStuff[0]][columnStuff[0]] = stuff[0];

	rowStuff[1] = 2 + rand() % (size_y / 3);
	columnStuff[1] = (size_x / 4) + (rand() % (size_x / 4));
	if (grid[rowStuff[1]][columnStuff[1]] == TILE_FLOOR)
		grid[rowStuff[1]][columnStuff[1]] = stuff[1];

	rowStuff[2] = 2 + rand() % (size_y / 3);
	columnStuff[2] = (size_x / 2) + (rand() % (size_x / 4));
	if (grid[rowStuff[2]][columnStuff[2]] == TILE_FLOOR)
		grid[rowStuff[2]][columnStuff[2]] = stuff[2];

	rowStuff[3] = (size_y / 2) + (rand() % ((size_y / 2) - 2));
	columnStuff[3] = 2 + (rand() % (size_x / 4));
	if (grid[rowStuff[3]][columnStuff[3]] == TILE_FLOOR)
		grid[rowStuff[3]][columnStuff[3]] = stuff[3];

	rowStuff[4] = (size_y / 2) + (rand() % ((size_y / 2) - 2));
	columnStuff[4] = (size_x / 4) + (rand() % (size_x / 4));
	if (grid[rowStuff[4]][columnStuff[4]] == TILE_FLOOR)
		grid[rowStuff[4]][columnStuff[4]] = stuff[4];

	rowStuff[5] = (size_y / 2) + (rand() % ((size_y / 2) - 2));
	columnStuff[5] = (size_x / 2) + (rand() % (size_x / 4));
	if (grid[rowStuff[5]][columnStuff[5]] == TILE_FLOOR)
		grid[rowStuff[5]][columnStuff[5]] = stuff[5];

	rowStuff[6] = (size_y / 2) + (rand() % ((size_y / 2) - 2));
	columnStuff[6] = (3 * size_x / 4) + ((rand() % (size_x / 4) - 2));
	if (grid[rowStuff[6]][columnStuff[6]] == TILE_FLOOR)
		grid[rowStuff[6]][columnStuff[6]] = stuff[6];

	return;
}*/
 
 /*int randpick(void)
 {
 	if(rand()%100 < fillprob)
 		return TILE_WALL;
 	else
 		return TILE_FLOOR;
 }*/

void ClearField()
{
	for (int i = 0; i < size_y; i++)
		for (int j = 0; j < size_x; j++)
			grid[i][j] = TILE_FLOOR;

	for (int i = 1; i < size_x; i++)
	{
		grid[0][i] = TILE_FLOOR;
		grid[1][i] = TILE_WALL;
		grid[size_y - 2][i] = TILE_WALL;
		grid[size_y - 1][i] = TILE_FLOOR;
	}
	for (int i = 1; i < size_y - 1; i++)
	{
		grid[i][0] = TILE_FLOOR;
		grid[i][1] = TILE_WALL;
		grid[i][size_x - 2] = TILE_WALL;
		grid[i][size_x - 1] = TILE_FLOOR;
	}

	grid[size_y - 1][1] = TILE_WALL;
	grid[size_y - 1][2] = TILE_WALL;
	grid[size_y - 1][3] = TILE_WALL;
	grid[size_y - 2][2] = TILE_FLOOR;
	grid[1][size_x - 3] = TILE_FLOOR;
}

void genRoom(int row, int column, int door)
{
	int **room;
	room = (int**)malloc(sizeof(int*) * (10));
 
	for(int yi = 0; yi < 10; ++yi)
		room[yi] = (int*)malloc(sizeof(int) * (20));

	int size_room_x = 20;
	int size_room_y = 10;
	int x = size_room_x / 2;
	int y = size_room_y / 2;

	for (int i = 0; i < size_room_y; ++i)
		for (int j = 0; j < size_room_x; ++j)
			room[i][j] = TILE_WALL;

// запускаем пьяного крота
	int fincell = 40;
	while (fincell > 0)
	{
		int direction = 1 + rand() % 4;
		switch (direction)
		{
			case 1:
				if (y > 2)
				{
					y--;
					if (room[y][x] == TILE_WALL)
					{
						room[y][x] = TILE_FLOOR;
						fincell--;
					}
				}
				else
				{
					x = size_room_x / 2;
					y = size_room_y / 2;
				}
				break;
			case 2:
				if (x < size_room_x - 3)
				{
					x++;
					if (room[y][x] == TILE_WALL)
					{
						room[y][x] = TILE_FLOOR;
						fincell--;
					}
				}
				else
				{
					x = size_room_x / 2;
					y = size_room_y / 2;
				}
				break;
			case 3:
				if (y < size_room_y - 3)
				{
					y++;
					if (room[y][x] == TILE_WALL)
					{
						room[y][x] = TILE_FLOOR;
						fincell--;
					}
				}
				else
				{
					x = size_room_x / 2;
					y = size_room_y / 2;
				}
				break;
			case 4:
				if (x > 2)
				{
					x--;
					if (room[y][x] == TILE_WALL)
					{
						room[y][x] = TILE_FLOOR;
						fincell--;
					}
				}
				else
				{
					x = size_room_x / 2;
					y = size_room_y / 2;
				}
				break;
		}
	}
	//

	x = size_room_x / 2;
	y = size_room_y / 2;

// удаляем лишние стенки вне комнаты
	for (int i = 1; i < size_room_y - 1; i++)
	{
		for (int j = 1; j < size_room_x - 1; j++)
			if ((room[i-1][j-1] == TILE_WALL || room[i-1][j-1] == TILE_POINT) &&
				(room[i-1][j] == TILE_WALL || room[i-1][j] == TILE_POINT) &&
				(room[i-1][j+1] == TILE_WALL || room[i-1][j+1] == TILE_POINT) &&
				(room[i][j-1] == TILE_WALL || room[i][j-1] == TILE_POINT) &&
				(room[i][j] == TILE_WALL || room[i][j] == TILE_POINT) &&
				(room[i][j+1] == TILE_WALL || room[i][j+1] == TILE_POINT) &&
				(room[i+1][j-1] == TILE_WALL || room[i+1][j-1] == TILE_POINT) &&
				(room[i+1][j] == TILE_WALL || room[i+1][j] == TILE_POINT) &&
				(room[i+1][j+1] == TILE_WALL || room[i+1][j+1] == TILE_POINT)
				)
				room[i][j] = TILE_POINT;
	}


	for (int i = 0; i < size_room_y; i++)
	{
		for (int j = 0; j < size_room_x; j++)
			if (room[i][j] == TILE_POINT)
				room[i][j] = TILE_FLOOR;
	}

	for (int i = 0; i < size_room_y; i++)
	{
		room[i][0] = TILE_FLOOR;
		room[i][size_room_x - 1] = TILE_FLOOR;
	}
	for (int i = 0; i < size_room_x; i++)
	{
		room[0][i] = TILE_FLOOR;
		room[size_room_y - 1][i] = TILE_FLOOR;
	}
	//

// обрезаем квадрат до размера комнаты
	int top = 0;
	for (int i = 0; i < size_room_y; ++i)
	{
		bool isFloor = true;
		for (int j = 0; j < size_room_x; ++j)
			isFloor &= room[i][j] == TILE_FLOOR;
		if (isFloor)
			top = i;
		else 
			break;
	}
	top++;

	int bottom = size_room_y - 1;
	for (int i = size_room_y - 1; i >= 0; --i)
	{
		bool isFloor = true;
		for (int j = 0; j < size_room_x; ++j)
			isFloor &= room[i][j] == TILE_FLOOR;
		if (isFloor)
			bottom = i;
		else 
			break;
	}

	int left = 0;
	for (int i = 0; i < size_room_x; ++i)
	{
		bool isFloor = true;
		for (int j = 0; j < size_room_y; ++j)
			isFloor &= room[j][i] == TILE_FLOOR;
		if (isFloor)
			left = i;
		else 
			break;
	}
	left++;

	int right = size_room_x - 1;
	for (int i = size_room_x - 1; i >= 0; --i)
	{
		bool isFloor = true;
		for (int j = 0; j < size_room_y; ++j)
			isFloor &= room[j][i] == TILE_FLOOR;
		if (isFloor)
			right = i;
		else 
			break;
	}
	//

// Бурим дверь в комнату
	bool isSetDoor = false;
	switch(1 + rand() % 4)
	{		
		case 1:
			for (int i = 1; i < right; ++i)
			{
				if (room[top][i-1] == TILE_WALL &&
					room[top][i] == TILE_WALL &&
					room[top][i+1] == TILE_WALL &&
					room[top+1][i] == TILE_FLOOR
					)
				{
					room[top][i] = TILE_DOOR;
					rowDoor[door] = top + row;
					columnDoor[door] = i + column;
					isSetDoor = true;
					break;
				}
			}
			if (isSetDoor)
				break;
		case 2:
			for (int i = top; i < bottom; ++i)
			{
				if (room[i-1][right] == TILE_WALL &&
					room[i][right] == TILE_WALL &&
					room[i+1][right] == TILE_WALL &&
					room[i][right-1] == TILE_FLOOR
					)
				{
					room[i][right] = TILE_DOOR;					
					rowDoor[door] = i + row;
					columnDoor[door] = right + column;
					isSetDoor = true;
					break;
				}
			}
			if (isSetDoor)
				break;
		case 3:
			for (int i = 1; i < right; ++i)
			{
				if (room[bottom][i-1] == TILE_WALL &&
					room[bottom][i] == TILE_WALL &&
					room[bottom][i+1] == TILE_WALL &&
					room[bottom-1][i] == TILE_FLOOR
					)
				{
					room[bottom][i] = TILE_DOOR;					
					rowDoor[door] = bottom + row;
					columnDoor[door] = i + column;
					isSetDoor = true;
					break;
				}
			}
			if (isSetDoor)
				break;
		case 4:
			for (int i = top; i < bottom; ++i)
			{
				if (room[i-1][left] == TILE_WALL &&
					room[i][left] == TILE_WALL &&
					room[i+1][left] == TILE_WALL &&
					room[i][left+1] == TILE_FLOOR
					)
				{
					room[i][left] = TILE_DOOR;					
					rowDoor[door] = i + row;
					columnDoor[door] = left + column;
					isSetDoor = true;
					break;
				}
			}
			if (isSetDoor)
				break;
	}
	//


// Пишем комнату в лабиринт
	for (int i = top; i < bottom; ++i)
	{
		for (int j = left; j < right; ++j)
		{
			if (room[i][j] == TILE_FLOOR)
				grid[i + row][j + column] = TILE_POINT;
			else
				grid[i + row][j + column] = room[i][j];
		}
	}
}

void genRooms()
{
	int row = 2 + rand() % (size_y / 5);
	int column = 2 + (rand() % (size_x / 8));
	genRoom(row, column, 0);

	row = 2 + rand() % (size_y / 5);
	column = (size_x / 4) + (rand() % (size_x / 8));
	genRoom(row, column, 1);

	row = 2 + rand() % (size_y / 5);
	column = (size_x / 2) + (rand() % (size_x / 8));
	genRoom(row, column, 2);

	row = (size_y / 2) + (rand() % (size_y / 4));
	column = 2 + (rand() % (size_x / 8));
	genRoom(row, column, 3);

	row = (size_y / 2) + (rand() % (size_y / 4));
	column = (size_x / 4) + (rand() % (size_x / 8));
	genRoom(row, column, 4);

	row = (size_y / 2) + (rand() % (size_y / 4));
	column = (size_x / 2) + (rand() % (size_x / 8));
	genRoom(row, column, 5);

	row = (size_y / 2) + (rand() % (size_y / 4));
	column = (3 * size_x / 4) + ((rand() % (size_x / 8)));
	genRoom(row, column, 6);

	return;
}
 
void initmap(void)
 {
	int xi, yi;

	grid  = (int**)malloc(sizeof(int*) * (size_y+3));
 
	for(yi=0; yi<size_y; yi++)
		grid[yi] = (int*)malloc(sizeof(int) * (size_x+3));

	
	ClearField();	
	genRooms();
	Generate();
}
 
string GetRenderCellSymbolWall(int r, int c)
{
	if ((r > 0) && (r < size_y) && (c > 0) && (c < size_x))
	{
		if ((grid[r + 1][c] == TILE_WALL) && (grid[r - 1][c] == TILE_WALL) && (grid[r][c + 1] == TILE_WALL) && (grid[r][c - 1] == TILE_WALL))
			return "\u253C";
		else if ((grid[r + 1][c] != TILE_WALL) && (grid[r - 1][c] == TILE_WALL) && (grid[r][c + 1] == TILE_WALL) && (grid[r][c - 1] == TILE_WALL))
			return "\u2534";
		else if ((grid[r + 1][c] == TILE_WALL) && (grid[r - 1][c] == TILE_WALL) && (grid[r][c + 1] != TILE_WALL) && (grid[r][c - 1] == TILE_WALL))
			return "\u2524";
		else if ((grid[r + 1][c] == TILE_WALL) && (grid[r - 1][c] == TILE_WALL) && (grid[r][c + 1] == TILE_WALL) && (grid[r][c - 1] != TILE_WALL))
			return "\u251C";
		else if ((grid[r + 1][c] == TILE_WALL) && (grid[r - 1][c] != TILE_WALL) && (grid[r][c + 1] == TILE_WALL) && (grid[r][c - 1] == TILE_WALL))
			return "\u252C";
		else if ((grid[r + 1][c] == TILE_WALL) && (grid[r - 1][c] == TILE_WALL) && (grid[r][c + 1] != TILE_WALL) && (grid[r][c - 1] != TILE_WALL))
			return "\u2502";
		else if ((grid[r + 1][c] != TILE_WALL) && (grid[r - 1][c] != TILE_WALL) && (grid[r][c + 1] == TILE_WALL) && (grid[r][c - 1] == TILE_WALL))
			return "\u2500";
		else if ((grid[r + 1][c] != TILE_WALL) && (grid[r - 1][c] == TILE_WALL) && (grid[r][c + 1] != TILE_WALL) && (grid[r][c - 1] == TILE_WALL))
			return "\u2518";
		else if ((grid[r + 1][c] != TILE_WALL) && (grid[r - 1][c] == TILE_WALL) && (grid[r][c + 1] == TILE_WALL) && (grid[r][c - 1] != TILE_WALL))
			return "\u2514";
		else if ((grid[r + 1][c] == TILE_WALL) && (grid[r - 1][c] != TILE_WALL) && (grid[r][c + 1] == TILE_WALL) && (grid[r][c - 1] != TILE_WALL))
			return "\u250C";
		else if ((grid[r + 1][c] == TILE_WALL) && (grid[r - 1][c] != TILE_WALL) && (grid[r][c + 1] != TILE_WALL) && (grid[r][c - 1] == TILE_WALL))
			return "\u2510";
		else if ((grid[r + 1][c] != TILE_WALL) && (grid[r - 1][c] == TILE_WALL) && (grid[r][c + 1] != TILE_WALL) && (grid[r][c - 1] != TILE_WALL))
			return "\u2575";
		else if ((grid[r + 1][c] != TILE_WALL) && (grid[r - 1][c] != TILE_WALL) && (grid[r][c + 1] == TILE_WALL) && (grid[r][c - 1] != TILE_WALL))
			return "\u2576";
		else if ((grid[r + 1][c] == TILE_WALL) && (grid[r - 1][c] != TILE_WALL) && (grid[r][c + 1] != TILE_WALL) && (grid[r][c - 1] != TILE_WALL))
			return "\u2577";
		else if ((grid[r + 1][c] != TILE_WALL) && (grid[r - 1][c] != TILE_WALL) && (grid[r][c + 1] != TILE_WALL) && (grid[r][c - 1] == TILE_WALL))
			return "\u2574";
	}

	return " ";
}
 
void printmap(void)
 {
 	int xi, yi;
 
 	for(yi=0; yi<size_y; yi++)
 	{
 		for(xi=0; xi<size_x; xi++)
 		{
 			switch(grid[yi][xi]) 
 			{
 				case TILE_WALL: cout << GetRenderCellSymbolWall(yi, xi); break;
 				//case TILE_WALL:  putchar('#'); break;
 				case TILE_FLOOR: putchar(' '); break;
 				case TILE_POINT: putchar(' '); break;
 				case TILE_DOOR: putchar('D'); break;
 			}
 		}
 		putchar('\n');
 	}
 }
 
int main(int argc, char **argv)
 {
 	int ii, jj;

 	size_x     = 100;
 	size_y     = 30;
 
 	srand(time(NULL));
 	initmap();
 	
 	for (int i = 1; i < size_x; i++)
	{
		grid[0][i] = TILE_FLOOR;
		grid[1][i] = TILE_WALL;
		grid[size_y - 2][i] = TILE_WALL;
		grid[size_y - 1][i] = TILE_FLOOR;
	}
	for (int i = 1; i < size_y - 1; i++)
	{
		grid[i][0] = TILE_FLOOR;
		grid[i][1] = TILE_WALL;
		grid[i][size_x - 2] = TILE_WALL;
		grid[i][size_x - 1] = TILE_FLOOR;
	}

 	printmap();
 	return 0;
}