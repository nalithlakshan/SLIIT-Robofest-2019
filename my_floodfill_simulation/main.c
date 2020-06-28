#include <stdio.h>
#include <stdlib.h>
#include <time.h>  //Not Necessary for STM**************
#include "global_space_floodfill.h"
#include "function_prototype.h"


void delay(int number_of_seconds) ; //Not Necessary for STM**************

//Function Header Includes
#include "maze_functions.h"
#include "mouse_position_functions.h"
#include "floodfill_functions.h"
#include "next_move_gen.h"
#include "simulation.h"




void main(){


setup_simulation();
int number_of_moves=0;


set_target_center();
SimpleFloodFillSolve(&flood);
number_of_moves=0;
while(MazeGetDistance(&maze, state.pos.x, state.pos.y)!=0){
    SimpleFloodFillSolve(&flood);
    execute_move();
    sensor_copy();
    print_mouse_position();
    MazePrint(&maze,4,4);
    number_of_moves++;
}
printf("No of move to center: %d\n",number_of_moves);



set_target_home();
SimpleFloodFillSolve(&flood);
number_of_moves=0;
while(MazeGetDistance(&maze, state.pos.x, state.pos.y)!=0){
    SimpleFloodFillSolve(&flood);
    execute_move();
    sensor_copy();
    print_mouse_position();
    MazePrint(&maze,4,4);
    number_of_moves++;
}
printf("No of move to home: %d\n",number_of_moves);



// set_target_center();
// SimpleFloodFillSolve(&flood);
// number_of_moves=0;
// while(MazeGetDistance(&maze, state.pos.x, state.pos.y)!=0){
//     SimpleFloodFillSolve(&flood);
//     execute_move();
//     sensor_copy();
//     print_mouse_position();
//     MazePrint(&maze,4,4);
//     number_of_moves++;
// }
// printf("No of move to center: %d\n",number_of_moves);



// set_target_home();
// SimpleFloodFillSolve(&flood);
// number_of_moves=0;
// while(MazeGetDistance(&maze, state.pos.x, state.pos.y)!=0){
//     SimpleFloodFillSolve(&flood);
//     execute_move();
//     sensor_copy();
//     print_mouse_position();
//     MazePrint(&maze,4,4);
//     number_of_moves++;

//     if(number_of_moves==10){
//         break;
//     }
// }
//printf("No of move to home: %d\n",number_of_moves);



    while(1){
       break; 
    }
}





