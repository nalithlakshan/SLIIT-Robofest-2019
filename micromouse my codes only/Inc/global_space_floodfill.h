#ifndef GLOBAL_SPACE_FLOODFILL_H_
#define GLOBAL_SPACE_FLOODFILL_H_


/*$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$*/
typedef struct MazeCell
{
    char x, y;
    char westWall, northWall;
    int distance;
    int explored;
    int inPath; // Used for printing out in debugger.    

} MazeCell;

typedef enum Compass
{
    WEST,
    NORTH,
    EAST,
    SOUTH,
    NONE
} Compass;

typedef enum Direction
{
    FORWARD,
    LEFT,
    RIGHT,
    BACK
} Direction;

/**
 * keeps track of the current status of the maze.
 */
typedef struct Maze
{
    /**
     * Maze Cells go from top left to bottom right. Note: the extra 17th cell 
     * is needed as there are 17 walls side to side and 17 walls up and down,
     * even though that only makes up 16 "cells".
     */
    MazeCell maze[15][15];
} Maze;



/*$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$*/

typedef struct MousePosition
{
    int x;
    int y;
    Compass forwardDirection;
} MousePosition;


typedef struct RobotState
{
    MousePosition pos;
    
    char targetXmin, targetXmax, targetYmin, targetYmax;
} RobotState;


/*$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$*/
/**
 * This is a simple implementation of a stack data structure
 */
typedef struct Stack
{
    /**
     * Represents the current position of the pointer on the stack
     */
    int pos;

    /**
     * This is the stack in it's entirity
     */
    void* nodes[125];
} Stack;

typedef struct XYTCoords
{
    unsigned char x, y;
    unsigned int level;
    Compass direction;
    int isInQueue;

} XYTCoords;

typedef struct FloodFill
{
    Maze* maze;
    RobotState* state;
} FloodFill;





//Final Globals
Maze maze;
RobotState state;
FloodFill flood;

Maze sim_maze;

#endif