void MazeInit(Maze* this)
{
    MazeReset(this);
}

void MazeReset(Maze* this)
{
    int i, j;
    
    MazeResetDistances(this);

    // Set all walls to not-set
    for (i = 0; i < 15; i++)
    {
        for (j = 0; j < 15; j++)
        {
            this->maze[i][j].northWall = 0;
            this->maze[i][j].westWall = 0;
            this->maze[i][j].explored = 0;
            this->maze[i][j].inPath = 0;
        }
    }

    for (i = 0; i < 14; i++)
    {
        MazeSetWall(this, i, 0, 1, NORTH);
        MazeSetWall(this, i, 13, 1, SOUTH);
        MazeSetWall(this, 0, i, 1, WEST);
        MazeSetWall(this, 13, i, 1, EAST);
    }
}

void MazeResetDistances(Maze* this)
{
    int x, y;
    
    for (x = 0; x < 15; x++)
    {
        for (y = 0; y < 15; y++)
        {
            this->maze[x][y].distance = 255; 
            this->maze[x][y].x = x;
            this->maze[x][y].y = y; 
        }
    }
}

void MazeSetWallRelative(Maze* this,
	int x, int y, int value,
	Compass forwardDir, Direction relativeDir)
{
	// Facing up
    if (forwardDir == NORTH)
    {
        if (relativeDir == FORWARD) MazeSetWall(this, x, y, value, NORTH);
        else if (relativeDir == RIGHT) MazeSetWall(this, x, y, value, EAST);
        else if (relativeDir == LEFT) MazeSetWall(this, x, y, value, WEST);
        else if (relativeDir == BACK) MazeSetWall(this, x, y, value, SOUTH);
    }
    // Facing down
    else if (forwardDir == SOUTH)
    {
        if (relativeDir == FORWARD) MazeSetWall(this, x, y, value, SOUTH);
        else if (relativeDir == RIGHT) MazeSetWall(this, x, y, value, WEST);
        else if (relativeDir == LEFT) MazeSetWall(this, x, y, value, EAST);
        else if (relativeDir == BACK) MazeSetWall(this, x, y, value, NORTH);
    }
    // Facing right
    else if (forwardDir == EAST)
    {
        if (relativeDir == FORWARD) MazeSetWall(this, x, y, value, EAST);
        else if (relativeDir == RIGHT) MazeSetWall(this, x, y, value, SOUTH);
        else if (relativeDir == LEFT) MazeSetWall(this, x, y, value, NORTH);
        else if (relativeDir == BACK) MazeSetWall(this, x, y, value, WEST);
    }
    // Facing left
    else if (forwardDir == WEST)
    {
        if (relativeDir == FORWARD) MazeSetWall(this, x, y, value, WEST);
        else if (relativeDir == RIGHT) MazeSetWall(this, x, y, value, NORTH);
        else if (relativeDir == LEFT) MazeSetWall(this, x, y, value, SOUTH);
        else if (relativeDir == BACK) MazeSetWall(this, x, y, value, EAST);
    }
}

void MazeSetWall(Maze* this, int x, int y, int value, Compass compass)
{
    if (compass == WEST)
        this->maze[x][y].westWall = value;

    else if (compass == NORTH)
        this->maze[x][y].northWall = value;

    else if (compass == EAST)
        this->maze[x+1][y].westWall = value;

    else if (compass == SOUTH)
        this->maze[x][y+1].northWall = value; 
}

void MazeSetDistance(Maze* this, int x, int y, int distance)
{
    this->maze[x][y].distance = distance; 
}

int MazeGetDistance(Maze* this, int x, int y)
{
    return this->maze[x][y].distance;
}

MazeCell* MazeGetCell(Maze* this, int x, int y)
{
    return &this->maze[x][y];
}

int MazeHasAWall(Maze* this, int x, int y, Compass compass)
{
    if (compass == WEST)
        return this->maze[x][y].westWall;

    else if (compass == NORTH)
        return this->maze[x][y].northWall;

    else if (compass == EAST)
        return this->maze[x+1][y].westWall;

    else if (compass == SOUTH)
        return this->maze[x][y+1].northWall;

    return 0;
}

int MazeHasAWallRelative(Maze* this, int x, int y, Compass forwardDir, Direction relativeDir)
{
    // Facing up
    if (forwardDir == NORTH)
    {
        if (relativeDir == FORWARD) return MazeHasAWall(this, x, y, NORTH);
        else if (relativeDir == RIGHT) return MazeHasAWall(this, x, y, EAST);
        else if (relativeDir == LEFT) return MazeHasAWall(this, x, y, WEST);
        else if (relativeDir == BACK) return MazeHasAWall(this, x, y, SOUTH);
    }
    // Facing down
    else if (forwardDir == SOUTH)
    {
        if (relativeDir == FORWARD) return MazeHasAWall(this, x, y, SOUTH);
        else if (relativeDir == RIGHT) return MazeHasAWall(this, x, y, WEST);
        else if (relativeDir == LEFT) return MazeHasAWall(this, x, y, EAST);
        else if (relativeDir == BACK) return MazeHasAWall(this, x, y, NORTH);
    }
    // Facing right
    else if (forwardDir == EAST)
    {
        if (relativeDir == FORWARD) return MazeHasAWall(this, x, y, EAST);
        else if (relativeDir == RIGHT) return MazeHasAWall(this, x, y, SOUTH);
        else if (relativeDir == LEFT) return MazeHasAWall(this, x, y, NORTH);
        else if (relativeDir == BACK) return MazeHasAWall(this, x, y, WEST);
    }
    // Facing left
    else if (forwardDir == WEST)
    {
        if (relativeDir == FORWARD) return MazeHasAWall(this, x, y, WEST);
        else if (relativeDir == RIGHT) return MazeHasAWall(this, x, y, NORTH);
        else if (relativeDir == LEFT) return MazeHasAWall(this, x, y, SOUTH);
        else if (relativeDir == BACK) return MazeHasAWall(this, x, y, EAST);
    }

    return 0;
}

// Returns a pointer to the cell adjacent to the current one.
MazeCell* MazeGetAdjacentCell(Maze* this, int x, int y, Compass compass)
{
    if (compass == NORTH && y > 0)
        return MazeGetCell(this, x, y-1);

    else if (compass == SOUTH && y < 13)
        return MazeGetCell(this, x, y+1);

    else if (compass == WEST && x > 0)
        return MazeGetCell(this, x-1, y);

    else if (compass == EAST && x < 13)
        return MazeGetCell(this, x+1, y);

    return 0;
}

MazeCell* MazeGetRelativeAdjacentCell(Maze* this, int x, int y, Compass forwardDir, Direction relativeDir)
{
    // Facing up
    if (forwardDir == NORTH)
    {
        if(relativeDir == FORWARD) return MazeGetAdjacentCell(this, x, y, NORTH);
        else if(relativeDir == RIGHT) return MazeGetAdjacentCell(this, x, y, EAST);
        else if(relativeDir == LEFT) return MazeGetAdjacentCell(this, x, y, WEST);
        else if(relativeDir == BACK) return MazeGetAdjacentCell(this, x, y, SOUTH);
    }
    // Facing down
    else if (forwardDir == SOUTH)
    {
        if(relativeDir == FORWARD) return MazeGetAdjacentCell(this, x, y, SOUTH);
        else if(relativeDir == RIGHT) return MazeGetAdjacentCell(this, x, y, WEST);
        else if(relativeDir == LEFT) return MazeGetAdjacentCell(this, x, y, EAST);
        else if(relativeDir == BACK) return MazeGetAdjacentCell(this, x, y, NORTH);
    }
    // Facing right
    else if (forwardDir == EAST)
    {
        if(relativeDir == FORWARD) return MazeGetAdjacentCell(this, x, y, EAST);
        else if(relativeDir == RIGHT) return MazeGetAdjacentCell(this, x, y, SOUTH);
        else if(relativeDir == LEFT) return MazeGetAdjacentCell(this, x, y, NORTH);
        else if(relativeDir == BACK) return MazeGetAdjacentCell(this, x, y, WEST);
    }
    // Facing left
    else if (forwardDir == WEST)
    {
        if(relativeDir == FORWARD) return MazeGetAdjacentCell(this, x, y, WEST);
        else if(relativeDir == RIGHT) return MazeGetAdjacentCell(this, x, y, NORTH);
        else if(relativeDir == LEFT) return MazeGetAdjacentCell(this, x, y, SOUTH);
        else if(relativeDir == BACK) return MazeGetAdjacentCell(this, x, y, EAST);
    }

    return 0;
}


void MazePrint(Maze* this, int tarx, int tary)
{
    printf("Printing Maze\n");
    int x, y;

    for (y = 0; y < 15; y++)
    {
        // Print top walls
        for (x = 0; x < 16; x++)
        {
            if (x < 15)
                printf("+");

            if (x < 14)
            {
                if (MazeHasAWall(this, x, y, NORTH))
                    printf("---");
                else
                    printf("   ");
            }
        }

        printf("\n");

        if (y < 14)
        {
            // Print side walls and data
            for (x = 0; x < 16; x++)
            {
                if (x < 15)
                {
                    if (MazeHasAWall(this, x, y, WEST))
                        printf("|");
                    else
                        printf(" ");
                }

                if(x < 14)
                {
                     int distance = MazeGetDistance(this, x, y);
                    // if (x == tarx && y == tary)
                    //     printf("\033[1;32m");
                    // else if (this->maze[x][y].inPath)
                    //     printf("\033[1;33m");
                    // else
                    //     printf("\033[1;31m");

                    // printf("%3d\033[0m", distance);
                    if((x==state.pos.x)&&(y==state.pos.y)){
                        printf("<*>");
                    }
                    else if(countDigits(distance)==1){
                        printf("  %d", distance);
                    }
                    else if(countDigits(distance)==2){
                        printf(" %d", distance);
                    }
                    else if(countDigits(distance)==3){
                        printf("%d", distance);
                    }
                    else
                    {
                        printf("err");
                    }
                    
                }
            }
            printf("\n");
        }
    }    
}



int countDigits(int num){
  int count=0;
  if(num==0){
    return 1;
  }
  while(num != 0)
    {
        count++;
        num /= 10;
    }
    return count;
}
