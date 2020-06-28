

#include "global_space_floodfill.h"
#include "function_prototype.h"


void SimpleFloodFillSolve(FloodFill* this)
{
    int stopX = this->state->pos.x;    
    int stopY = this->state->pos.y;

    Stack stack1;
    Stack stack2; 
    StackInit(&stack1);
    StackInit(&stack2);

    Stack* pStack1;
    Stack* pStack2;

    pStack1 = &stack1;
    pStack2 = &stack2;
    
    // --- This heap stuff should be done somewhere else --
    int i;
    XYTCoords** xyt = malloc(sizeof(XYTCoords*[14]));
    for (i = 0; i < 14; i++)
        xyt[i] = malloc(sizeof(XYTCoords[14]));

    int tx, ty;
    for (tx = 0; tx < 14; tx++)
    {
        for (ty = 0; ty < 14; ty++)
        {
            xyt[tx][ty].x = tx;
            xyt[tx][ty].y = ty;
        }    
    }

    // ----------------------------------------------------

    int level = 0;
    int canGoInUnexploredCells = 1; // This should set by things in RobotState
    int forceQuit = 0;

    // Push target cells to the stack first
    int x, y;
    for (x = this->state->targetXmin; x <= this->state->targetXmax; x++)
    {
        for (y = this->state->targetYmin; y <= this->state->targetYmax; y++)
        {
            StackPush(pStack1, &xyt[x][y]);
        }
    }

    MazeResetDistances(this->maze);

    MazeCell* zeroCell = &this->maze->maze[0][0];

    while (pStack1->pos != -1 && !forceQuit)
    {
        int* pos = &pStack1->pos;
        void** nodes = pStack1->nodes;
        int* pos2 = &pStack2->pos;
        void** nodes2 = pStack2->nodes;
       
        while (*pos != -1)
        {
            int x = ((XYTCoords*)nodes[*pos])->x;
            int y = ((XYTCoords*)nodes[*pos])->y;
            (*pos)--;

            // Get the pointer to the main cell
            // mainCell = maze->maze[x][y]
            // mainCell = zeroCell + x*17 + y
            MazeCell* mainCell = zeroCell + x*15 + y; //MazeCell* mainCell = zeroCell + (x << 4) + x + y;

            // Optimized flood fill search, such confusion D:
            if(mainCell->distance == 255)
            {
                mainCell->distance = level;

                if (x == stopX && y == stopY)
                {
                    forceQuit = 1;
                    break;
                }

                MazeCell* rightCell = (x < 13) ? mainCell + 15 : mainCell;

                if((rightCell->distance == 255)
                    && (canGoInUnexploredCells == 1 || rightCell->explored)
                    &&!(rightCell->westWall))
                {
                    (*pos2)++;
                    nodes2[*pos2] = &xyt[x+1][y];
                }

                MazeCell* leftCell = (x > 0) ? mainCell - 15 : mainCell;

                if((leftCell->distance == 255)
                    && (canGoInUnexploredCells == 1 || leftCell->explored)
                    &&!(mainCell->westWall))
                { 
                    (*pos2)++;
                    nodes2[*pos2] = &xyt[x-1][y];
                }

                MazeCell* bottomCell = (y < 13) ? mainCell + 1 : mainCell;

                if((bottomCell->distance == 255)
                    && (canGoInUnexploredCells == 1 || bottomCell->explored)
                    &&!(bottomCell->northWall))
                {
                    (*pos2)++;
                    nodes2[*pos2] = &xyt[x][y+1];
                }

                MazeCell* upCell = (y > 0) ? mainCell - 1 : mainCell;

                if((upCell->distance == 255)
                    && (canGoInUnexploredCells == 1 || upCell->explored)
                    &&!(mainCell->northWall))
                {
                    (*pos2)++;
                    nodes2[*pos2] = &xyt[x][y-1];
                }
            }
        }
        
        level++;

        // Switch stacks by switching pointers
        // Much more efficient then copying values from one stack to the other.
        Stack* tmpPStack = pStack1;
        pStack1 = pStack2;
        pStack2 = tmpPStack;
    }


    for (i = 0; i < 12; i++)
        free(xyt[i]);
    free(xyt);
}


/*$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$*/

void StackInit(Stack* this)
{
    this->pos = -1;
}

void* StackPop(Stack* this)
{
    if (this->pos < 0)
    {
        this->pos = -1;
        return 0;
    }
    else
    {
        this->pos--;
        return this->nodes[this->pos+1];
    }
}

void StackPush(Stack* this, void* cell)
{
    this->pos++;
    this->nodes[this->pos] = cell; 
}

void* StackPeek(Stack* this)
{
    if (this->pos >= 0) return this->nodes[this->pos];

    return 0;
}

int StackIsEmpty(Stack* this)
{
    return (this->pos == -1);
}

void StackReset(Stack* this)
{
    this->pos = -1;
}












