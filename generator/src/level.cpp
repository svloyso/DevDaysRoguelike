#include "level.h"
#include "getLevel.h"

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

    //GenerateStuff(rowStuff, columnStuff);

    int from = 2*size_x + 2;
    int to = (size_y - 3) * size_x + size_x - 3; 

    grid[from / size_x][from % size_x] = TILE_EXIT;
    //grid[to / size_x][to % size_x] = TILE_EXIT;

    for (int i = 0; i < numDoor; i++)
    {
        for (int j = 0; j < num; j++)
            visited[j] = false;
        if (!exploreMatr(rowDoor[i] * size_x + columnDoor[i], to, visited))
        {
            rowDoor[i] = from / size_x;
            columnDoor[i] = from % size_x;
        }
    }

    
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
    
    // Убираем некрасивые выступы
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

    
    for (int i = 0; i < num; i++)
        visited[i] = false;
    GenerateMobs(from, to, visited);

    for (int i = 0; i < num; i++)
        visited[i] = false;
    GenerateKeys(from, to, visited);

    return;
}


bool GenerateMobs(int from, int to, bool* visited)
{
    bool isGoodPath = false;

    visited[from] = true;

    if (from == to)
        return true;

    int r = from / size_x;
    int c = from % size_x;

    if ((r + 1 > 0) && (r + 1 < size_y))
        if ((grid[r + 1][c] != TILE_WALL) && (!visited[(r + 1) * size_x + c]))
            isGoodPath |= GenerateMobs((r + 1) * size_x + c, to, visited);

    if ((r - 1 > 0) && (r - 1 < size_y))
        if ((grid[r - 1][c] != TILE_WALL) && (!visited[(r - 1) * size_x + c]))
            isGoodPath |= GenerateMobs((r - 1) * size_x + c, to, visited);

    if ((c + 1 > 0) && (c + 1 < size_x))
        if ((grid[r][c + 1] != TILE_WALL) && (!visited[r * size_x + c + 1]))
            isGoodPath |= GenerateMobs(r * size_x + c + 1, to, visited);

    if ((c - 1 > 0) && (c - 1 < size_x))
        if ((grid[r][c - 1] != TILE_WALL) && (!visited[r * size_x + c - 1]))
            isGoodPath |= GenerateMobs(r * size_x + c - 1, to, visited);

    if ((from != (size_y - 1) * size_x + 1) && (grid[r][c] == TILE_FLOOR))
    {
        for (int i = 0; i < numFractions; ++i)
        {
            if (rand() % 1000 < fraction[i].probability)
            {
                grid[r][c] = TILE_ORC;
                gridMob[r][c] = genMob(fraction[i]);
            }
        }
    }
    return isGoodPath;
}

int currNumKey = 0;

bool GenerateKeysInDFS(int from, int to, bool* visited)
{
    bool isGoodPath = false;

    visited[from] = true;

    if (from == to)
        return true;

    int r = from / size_x;
    int c = from % size_x;

    if ((r + 1 > 0) && (r + 1 < size_y))
        if ((grid[r + 1][c] != TILE_WALL) && (!visited[(r + 1) * size_x + c]))
            isGoodPath |= GenerateKeysInDFS((r + 1) * size_x + c, to, visited);

    if ((r - 1 > 0) && (r - 1 < size_y))
        if ((grid[r - 1][c] != TILE_WALL) && (!visited[(r - 1) * size_x + c]))
            isGoodPath |= GenerateKeysInDFS((r - 1) * size_x + c, to, visited);

    if ((c + 1 > 0) && (c + 1 < size_x))
        if ((grid[r][c + 1] != TILE_WALL) && (!visited[r * size_x + c + 1]))
            isGoodPath |= GenerateKeysInDFS(r * size_x + c + 1, to, visited);

    if ((c - 1 > 0) && (c - 1 < size_x))
        if ((grid[r][c - 1] != TILE_WALL) && (!visited[r * size_x + c - 1]))
            isGoodPath |= GenerateKeysInDFS(r * size_x + c - 1, to, visited);

	if ((from != (size_y - 1) * size_x + 1) && (grid[r][c] == TILE_FLOOR))
	    if ((currNumKey < numDoor) && (rand() % 1000 < 10))
	    {
            grid[r][c] = TILE_KEY;
            currNumKey++;
	    }

    return isGoodPath;
}

void GenerateKeys(int from, int to, bool* visited)
{
	// Генерим ключи на пути героя до конечной точки	
    GenerateKeysInDFS(from, to, visited);

    // Если сгенерили не все - догенерим в случайных местах
    while(currNumKey < numDoor)
    {
    	int r = 3 + rand() % (size_y - 3);
    	int c = 3 + rand() % (size_x - 3);

    	if (grid[r][c] == TILE_FLOOR)
    	{
    		grid[r][c] = TILE_KEY;
            currNumKey++;
    	}
    }
}

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

    size_room_x = 20;
    size_room_y = 10;
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

    // Пихаем в комнату предмет и трейку охранников
    x = size_room_x / 2;
    y = size_room_y / 2;

    grid[y][x] = TILE_ITEM;
    gridItem[y][x] = stuff[ rand() % stuff.size() ];

    for (int i = 0; i < 3; ++i)
    {
        if (room[y][x] == TILE_FLOOR)
        {
        	for (int i = 0; i < numFractions; ++i)
	        {
	            grid[y + (rand() % 4) + row][x + (rand() % 4) + column] = TILE_ORC;
	            gridMob[y + (rand() % 4) + row][x + (rand() % 4) + column] = genMob(fraction[i]);
	        }
        }
    }
}

void genRooms()
{
    for (int i = 0; i < size_y / (size_room_y + 5); ++i)
    {
        for (int j = 0; j < size_x / (size_room_x + 5); ++j)
        {
            if ((i == size_y / (size_room_y + 5) - 1) && (j == size_x / (size_room_x + 5) - 1))
                break;
            else
            {
                int row = i * (size_room_y + 5) + 2 + rand() % (size_room_y / 2);
                int column = j * (size_room_x + 5) + rand() % (size_room_x / 2);
                genRoom(row, column, i * size_x / (size_room_x + 5) + j);
            }
        }
    }
}
 
void initmap(void)
 {
    genFraction();
    genItems();

    grid = vector< vector<int> >(size_y+3, vector<int>(size_x+3));
    
    ClearField();   
    genRooms();
    Generate();

    // Поправил стенки, могли испортиться
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
}
 
void getMap()
{
    size_x     = 100;
    size_y     = 30;
 
    srand(time(NULL));
    initmap();

    vector< vector< TilePtr > > tiles;
    MapInfo info;
    info.size = Coord(size_y-2, size_x-2);
    info.hero_init = Coord(0, 0);
    
    for (int i = 1; i <= size_y-2; ++i)
    {
        vector< TilePtr > row;
        for (int j = 1; j < size_x-1; ++j)
        {
            TilePtr tile;
            std::vector< ImmovablePtr > imms;

            MyMob tempmob;
            MonsterStatsPtr m;
            SkeletonAIPtr skelAI;
            MonsterPtr mob;

            switch(grid[i][j]) 
            {
                case TILE_WALL:
                    tile = std::make_shared<WallTile>();
                    break;
                case TILE_DOOR:
                    imms.push_back(std::make_shared<Door>());
                    tile = std::make_shared<FloorTile>(UnitPtr(), std::vector<ItemPtr>(), imms);
                    break;
                case TILE_ORC:

                    tempmob = gridMob[i][j];

                    m = MonsterStats::make_Ptr();
                    m->strength = tempmob.strength;
                    m->hit_points = tempmob.health;
                    m->max_hit_points = tempmob.health;
                    m->area_of_sight = 5;
                    m->fraction = tempmob.fraction;

                    skelAI = SkeletonAI::make_Ptr();

                    mob = Monster::make_Ptr(skelAI, m);
                    tile = std::make_shared<FloorTile>(mob);

                    break;
                case TILE_EXIT:
                    info.hero_init = Coord(i-1, j-1);
                    tile = std::make_shared<FloorTile>();
                    break;
                default:
                    tile = std::make_shared<FloorTile>();
                    break;
            }
            row.push_back(tile);
        }
        tiles.push_back(row);
    }
    init_core(info, tiles);
}

bool fractPower(MyFraction i, MyFraction j)
{ 
    return ( i.health + i.strength < j.health + j.strength);
}

void genFraction()
{   
    for (int i = 0; i < numFractions; ++i)
    {
        fraction[i].name = i;
        fraction[i].health = 40 + rand() % 60;
        fraction[i].strength = 2 + rand() % 40;
        fraction[i].probability = 1 + rand() % 30;
    }

    sort(fraction.begin(), fraction.end(), fractPower);

    for (int i = 0; i < numFractions; ++i)
    {
        fraction[i].probability = 1 + rand() % ((numFractions - i) * maxProbability / numFractions);
    }
}

MyMob genMob(MyFraction fract)
{
    MyMob mob;
    mob.fraction = fract.name;
    mob.health = fract.health;
    mob.strength = fract.strength;
    for (int i = 0; i < 3; ++i)
    {
        int randnum = rand() % stuff.size();
        MyItem item = stuff[ randnum ];
        if (item.stat == strength)
            mob.strength += item.effect;
        else
            mob.health += item.effect;
        mob.inventory.push_back( item );
    }
    return mob;
}

void genItems()
{
    int num = 5 + rand() % 15;
    for (int i = 0; i < num; ++i)
    {
        MyItem it;
        it.type = weapon;
        it.stat = strength;
        it.effect = 1 + rand() % 40;
        stuff.push_back(it);
    }

    num = 5 + rand() % 15;
    for (int i = 0; i < num; ++i)
    {
        MyItem it;
        it.type = head;
        it.stat = health;
        it.effect = 1 + rand() % 40;
        stuff.push_back(it);
    }

    num = 5 + rand() % 15;
    for (int i = 0; i < num; ++i)
    {
        MyItem it;
        it.type = body;
        it.stat = health;
        it.effect = 1 + rand() % 40;
        stuff.push_back(it);
    }

    num = 5 + rand() % 15;
    for (int i = 0; i < num; ++i)
    {
        MyItem it;
        it.type = arms;
        it.stat = health;
        it.effect = 1 + rand() % 40;
        stuff.push_back(it);
    }

    num = 5 + rand() % 15;
    for (int i = 0; i < num; ++i)
    {
        MyItem it;
        it.type = legs;
        it.stat = health;
        it.effect = 1 + rand() % 40;
        stuff.push_back(it);
    }
}

/*int main(int argc, char **argv)
{
    srand(time(NULL));
    genFraction();
    genItems();
    initmap();    

    //printmap();
    return 0;
}*/