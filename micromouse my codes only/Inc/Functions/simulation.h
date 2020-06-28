void simulate(){

	HAL_Delay(4000);
	setup_simulation();
	int number_of_moves=0;

	set_target_center();
	while(MazeGetDistance(&maze, state.pos.x, state.pos.y)!=0){
		SimpleFloodFillSolve(&flood);
		execute_move_sim();
		sensor_copy_sim();
		print_mouse_position();
		MazePrint(&maze,4,4);
		number_of_moves++;
		HAL_Delay(100);
		// if(number_of_moves==20){
		//     break;
		// }
	}
	print("No of move to center: %d\n",number_of_moves);



	 set_target_home();

	 number_of_moves=0;
	 while(!(state.pos.x==0 && state.pos.y==13)){
		 SimpleFloodFillSolve(&flood);
		 execute_move_sim();
		 sensor_copy_sim();
		 print_mouse_position();
		 MazePrint(&maze,4,4);
		 number_of_moves++;
		 HAL_Delay(100);
	 }
	 print("No of move to home: %d\n",number_of_moves);


	// set_target_center();

	// number_of_moves=0;
	// while(!(state.pos.x==0 && state.pos.y==13)){
	//     SimpleFloodFillSolve(&flood);
	//     execute_move_sim();
	//     sensor_copy_sim();
	//     print_mouse_position();
	//     MazePrint(&maze,4,4);
	//     number_of_moves++;
	// }
	// printf("No of move to center: %d\n",number_of_moves);


}


void execute_move_sim(){
    char Move= MoveGenGetNextMove(&maze, state.pos.x, state.pos.y, state.pos.forwardDirection);
    print("%c\n",Move);
    if (Move=='F'|| Move=='f'){
        MousePositionGoForward(&state.pos);
    }
    else if (Move=='B'|| Move=='b'){
        MousePositionGoBackward(&state.pos);
    }
    else if (Move=='L'|| Move=='l'){
        MousePositionRotateLeft(&state.pos);
        MousePositionGoForward(&state.pos);
    }
    else if (Move=='R'|| Move=='r'){
        MousePositionRotateRight(&state.pos);
        MousePositionGoForward(&state.pos);
    }
    maze.maze[state.pos.x][state.pos.y].explored=1;
}

void sensor_copy_sim(){
    maze.maze[state.pos.x][state.pos.y].northWall=sim_maze.maze[state.pos.x][state.pos.y].northWall;
    maze.maze[state.pos.x][state.pos.y].westWall=sim_maze.maze[state.pos.x][state.pos.y].westWall;
    maze.maze[state.pos.x][state.pos.y+1].northWall=sim_maze.maze[state.pos.x][state.pos.y+1].northWall;
    maze.maze[state.pos.x+1][state.pos.y].westWall=sim_maze.maze[state.pos.x+1][state.pos.y].westWall;
}


void print_mouse_position(){
    print("Current x:%d  y:%d   ",state.pos.x,state.pos.y);
    if(state.pos.forwardDirection==NORTH){
        print("fwDir: North \n");
    }
    else if(state.pos.forwardDirection==SOUTH){
        print("fwDir: South \n");
    }
    else if(state.pos.forwardDirection==WEST){
        print("fwDir: West \n");
    }
    else if(state.pos.forwardDirection==EAST){
        print("fwDir: East \n");
    }
    else{
        print("Error Direction!!!!!!\n");
    }   
}


void set_target_center(){
    state.targetXmax=7;
    state.targetXmin=6;
    state.targetYmax=7;
    state.targetYmin=6;
}

void set_target_home(){
    state.targetXmax=0;
    state.targetXmin=0;
    state.targetYmax=13;
    state.targetYmin=13;
}


void setup_run(){
	flood.maze=&maze;
	flood.state=&state;
	MazeInit(&maze);
	MousePositionInit(&state.pos,EAST,0,13);
	maze.maze[state.pos.x][state.pos.y].explored=1;
}


void setup_simulation(){

    flood.maze=&maze;
    flood.state=&state;
    MazeInit(&maze);
    MousePositionInit(&state.pos,NORTH,0,13);
    maze.maze[state.pos.x][state.pos.y].explored=1;
    state.targetXmax=7;
    state.targetXmin=6;
    state.targetYmax=7;
    state.targetYmin=6;

    MazeInit(&sim_maze); //The virtual maze for simulation
    
    //Cells
    sim_maze.maze[0][0].westWall=1;sim_maze.maze[0][0].northWall=1;
    sim_maze.maze[1][0].westWall=0;sim_maze.maze[1][0].northWall=1;
    sim_maze.maze[2][0].westWall=0;sim_maze.maze[2][0].northWall=1;
    sim_maze.maze[3][0].westWall=0;sim_maze.maze[3][0].northWall=1;
    sim_maze.maze[4][0].westWall=0;sim_maze.maze[4][0].northWall=1;
    sim_maze.maze[5][0].westWall=0;sim_maze.maze[5][0].northWall=1;
    sim_maze.maze[6][0].westWall=0;sim_maze.maze[6][0].northWall=1;
    sim_maze.maze[7][0].westWall=0;sim_maze.maze[7][0].northWall=1;
    sim_maze.maze[8][0].westWall=0;sim_maze.maze[8][0].northWall=1;
    sim_maze.maze[9][0].westWall=1;sim_maze.maze[9][0].northWall=1;

    sim_maze.maze[0][1].westWall=1;sim_maze.maze[0][1].northWall=1;
    sim_maze.maze[1][1].westWall=0;sim_maze.maze[1][1].northWall=1;
    sim_maze.maze[2][1].westWall=0;sim_maze.maze[2][1].northWall=0;
    sim_maze.maze[3][1].westWall=0;sim_maze.maze[3][1].northWall=1;
    sim_maze.maze[4][1].westWall=1;sim_maze.maze[4][1].northWall=0;
    sim_maze.maze[5][1].westWall=0;sim_maze.maze[5][1].northWall=1;
    sim_maze.maze[6][1].westWall=1;sim_maze.maze[6][1].northWall=0;
    sim_maze.maze[7][1].westWall=0;sim_maze.maze[7][1].northWall=1;
    sim_maze.maze[8][1].westWall=0;sim_maze.maze[8][1].northWall=1;
    sim_maze.maze[9][1].westWall=1;sim_maze.maze[9][1].northWall=0;

    sim_maze.maze[0][2].westWall=1;sim_maze.maze[0][2].northWall=1;
    sim_maze.maze[1][2].westWall=0;sim_maze.maze[1][2].northWall=1;
    sim_maze.maze[2][2].westWall=0;sim_maze.maze[2][2].northWall=1;
    sim_maze.maze[3][2].westWall=1;sim_maze.maze[3][2].northWall=0;
    sim_maze.maze[4][2].westWall=1;sim_maze.maze[4][2].northWall=0;
    sim_maze.maze[5][2].westWall=0;sim_maze.maze[5][2].northWall=1;
    sim_maze.maze[6][2].westWall=0;sim_maze.maze[6][2].northWall=0;
    sim_maze.maze[7][2].westWall=1;sim_maze.maze[7][2].northWall=0;
    sim_maze.maze[8][2].westWall=1;sim_maze.maze[8][2].northWall=0;
    sim_maze.maze[9][2].westWall=1;sim_maze.maze[9][2].northWall=0;

    sim_maze.maze[0][3].westWall=1;sim_maze.maze[0][3].northWall=1;
    sim_maze.maze[1][3].westWall=0;sim_maze.maze[1][3].northWall=1;
    sim_maze.maze[2][3].westWall=1;sim_maze.maze[2][3].northWall=0;
    sim_maze.maze[3][3].westWall=1;sim_maze.maze[3][3].northWall=0;
    sim_maze.maze[4][3].westWall=1;sim_maze.maze[4][3].northWall=0;
    sim_maze.maze[5][3].westWall=0;sim_maze.maze[5][3].northWall=1;
    sim_maze.maze[6][3].westWall=0;sim_maze.maze[6][3].northWall=1;
    sim_maze.maze[7][3].westWall=0;sim_maze.maze[7][3].northWall=0;
    sim_maze.maze[8][3].westWall=1;sim_maze.maze[8][3].northWall=0;
    sim_maze.maze[9][3].westWall=1;sim_maze.maze[9][3].northWall=0;

    sim_maze.maze[0][4].westWall=1;sim_maze.maze[0][4].northWall=0;
    sim_maze.maze[1][4].westWall=1;sim_maze.maze[1][4].northWall=0;
    sim_maze.maze[2][4].westWall=1;sim_maze.maze[2][4].northWall=0;
    sim_maze.maze[3][4].westWall=0;sim_maze.maze[3][4].northWall=0;
    sim_maze.maze[4][4].westWall=1;sim_maze.maze[4][4].northWall=0;
    sim_maze.maze[5][4].westWall=1;sim_maze.maze[5][4].northWall=0;
    sim_maze.maze[6][4].westWall=1;sim_maze.maze[6][4].northWall=1;
    sim_maze.maze[7][4].westWall=0;sim_maze.maze[7][4].northWall=1;
    sim_maze.maze[8][4].westWall=0;sim_maze.maze[8][4].northWall=0;
    sim_maze.maze[9][4].westWall=1;sim_maze.maze[9][4].northWall=0;

    sim_maze.maze[0][5].westWall=1;sim_maze.maze[0][5].northWall=0;
    sim_maze.maze[1][5].westWall=1;sim_maze.maze[1][5].northWall=0;
    sim_maze.maze[2][5].westWall=0;sim_maze.maze[2][5].northWall=0;
    sim_maze.maze[3][5].westWall=1;sim_maze.maze[3][5].northWall=0;
    sim_maze.maze[4][5].westWall=1;sim_maze.maze[4][5].northWall=1;
    sim_maze.maze[5][5].westWall=0;sim_maze.maze[5][5].northWall=0;
    sim_maze.maze[6][5].westWall=0;sim_maze.maze[6][5].northWall=1;
    sim_maze.maze[7][5].westWall=0;sim_maze.maze[7][5].northWall=1;
    sim_maze.maze[8][5].westWall=0;sim_maze.maze[8][5].northWall=1;
    sim_maze.maze[9][5].westWall=1;sim_maze.maze[9][5].northWall=0;

    sim_maze.maze[0][6].westWall=1;sim_maze.maze[0][6].northWall=0;
    sim_maze.maze[1][6].westWall=1;sim_maze.maze[1][6].northWall=0;
    sim_maze.maze[2][6].westWall=1;sim_maze.maze[2][6].northWall=1;
    sim_maze.maze[3][6].westWall=0;sim_maze.maze[3][6].northWall=0;
    sim_maze.maze[4][6].westWall=1;sim_maze.maze[4][6].northWall=0;
    sim_maze.maze[5][6].westWall=1;sim_maze.maze[5][6].northWall=1;
    sim_maze.maze[6][6].westWall=0;sim_maze.maze[6][6].northWall=1;
    sim_maze.maze[7][6].westWall=0;sim_maze.maze[7][6].northWall=1;
    sim_maze.maze[8][6].westWall=1;sim_maze.maze[8][6].northWall=0;
    sim_maze.maze[9][6].westWall=1;sim_maze.maze[9][6].northWall=0;

    sim_maze.maze[0][7].westWall=1;sim_maze.maze[0][7].northWall=1;
    sim_maze.maze[1][7].westWall=0;sim_maze.maze[1][7].northWall=0;
    sim_maze.maze[2][7].westWall=0;sim_maze.maze[2][7].northWall=0;
    sim_maze.maze[3][7].westWall=0;sim_maze.maze[3][7].northWall=1;
    sim_maze.maze[4][7].westWall=0;sim_maze.maze[4][7].northWall=0;
    sim_maze.maze[5][7].westWall=1;sim_maze.maze[5][7].northWall=0;
    sim_maze.maze[6][7].westWall=1;sim_maze.maze[6][7].northWall=0;
    sim_maze.maze[7][7].westWall=0;sim_maze.maze[7][7].northWall=0;
    sim_maze.maze[8][7].westWall=1;sim_maze.maze[8][7].northWall=0;
    sim_maze.maze[9][7].westWall=1;sim_maze.maze[9][7].northWall=0;

    sim_maze.maze[0][8].westWall=1;sim_maze.maze[0][8].northWall=0;
    sim_maze.maze[1][8].westWall=0;sim_maze.maze[1][8].northWall=1;
    sim_maze.maze[2][8].westWall=0;sim_maze.maze[2][8].northWall=1;
    sim_maze.maze[3][8].westWall=1;sim_maze.maze[3][8].northWall=0;
    sim_maze.maze[4][8].westWall=1;sim_maze.maze[4][8].northWall=1;
    sim_maze.maze[5][8].westWall=0;sim_maze.maze[5][8].northWall=0;
    sim_maze.maze[6][8].westWall=0;sim_maze.maze[6][8].northWall=1;
    sim_maze.maze[7][8].westWall=0;sim_maze.maze[7][8].northWall=1;
    sim_maze.maze[8][8].westWall=0;sim_maze.maze[8][8].northWall=0;
    sim_maze.maze[9][8].westWall=1;sim_maze.maze[9][8].northWall=0;

    sim_maze.maze[0][9].westWall=1;sim_maze.maze[0][9].northWall=1;
    sim_maze.maze[1][9].westWall=0;sim_maze.maze[1][9].northWall=1;
    sim_maze.maze[2][9].westWall=0;sim_maze.maze[2][9].northWall=1;
    sim_maze.maze[3][9].westWall=0;sim_maze.maze[3][9].northWall=0;
    sim_maze.maze[4][9].westWall=1;sim_maze.maze[4][9].northWall=0;
    sim_maze.maze[5][9].westWall=0;sim_maze.maze[5][9].northWall=1;
    sim_maze.maze[6][9].westWall=0;sim_maze.maze[6][9].northWall=1;
    sim_maze.maze[7][9].westWall=0;sim_maze.maze[7][9].northWall=1;
    sim_maze.maze[8][9].westWall=0;sim_maze.maze[8][9].northWall=1;
    sim_maze.maze[9][9].westWall=1;sim_maze.maze[9][9].northWall=0;

    sim_maze.maze[0][10].westWall=1;sim_maze.maze[0][10].northWall=0;
    sim_maze.maze[1][10].westWall=0;sim_maze.maze[1][10].northWall=1;
    sim_maze.maze[2][10].westWall=1;sim_maze.maze[2][10].northWall=0;
    sim_maze.maze[3][10].westWall=1;sim_maze.maze[3][10].northWall=1;
    sim_maze.maze[4][10].westWall=0;sim_maze.maze[4][10].northWall=0;
    sim_maze.maze[5][10].westWall=1;sim_maze.maze[5][10].northWall=1;
    sim_maze.maze[6][10].westWall=0;sim_maze.maze[6][10].northWall=0;
    sim_maze.maze[7][10].westWall=1;sim_maze.maze[7][10].northWall=0;
    sim_maze.maze[8][10].westWall=1;sim_maze.maze[8][10].northWall=0;
    sim_maze.maze[9][10].westWall=1;sim_maze.maze[9][10].northWall=0;

    sim_maze.maze[0][11].westWall=1;sim_maze.maze[0][11].northWall=0;
    sim_maze.maze[1][11].westWall=1;sim_maze.maze[1][11].northWall=0;
    sim_maze.maze[2][11].westWall=1;sim_maze.maze[2][11].northWall=0;
    sim_maze.maze[3][11].westWall=0;sim_maze.maze[3][11].northWall=1;
    sim_maze.maze[4][11].westWall=0;sim_maze.maze[4][11].northWall=0;
    sim_maze.maze[5][11].westWall=1;sim_maze.maze[5][11].northWall=0;
    sim_maze.maze[6][11].westWall=1;sim_maze.maze[6][11].northWall=1;
    sim_maze.maze[7][11].westWall=0;sim_maze.maze[7][11].northWall=0;
    sim_maze.maze[8][11].westWall=1;sim_maze.maze[8][11].northWall=0;
    sim_maze.maze[9][11].westWall=1;sim_maze.maze[9][11].northWall=0;

    sim_maze.maze[0][12].westWall=1;sim_maze.maze[0][12].northWall=0;
    sim_maze.maze[1][12].westWall=1;sim_maze.maze[1][12].northWall=0;
    sim_maze.maze[2][12].westWall=1;sim_maze.maze[2][12].northWall=0;
    sim_maze.maze[3][12].westWall=1;sim_maze.maze[3][12].northWall=1;
    sim_maze.maze[4][12].westWall=0;sim_maze.maze[4][12].northWall=0;
    sim_maze.maze[5][12].westWall=1;sim_maze.maze[5][12].northWall=0;
    sim_maze.maze[6][12].westWall=0;sim_maze.maze[6][12].northWall=1;
    sim_maze.maze[7][12].westWall=0;sim_maze.maze[7][12].northWall=1;
    sim_maze.maze[8][12].westWall=0;sim_maze.maze[8][12].northWall=0;
    sim_maze.maze[9][12].westWall=1;sim_maze.maze[9][12].northWall=0;

    sim_maze.maze[0][13].westWall=1;sim_maze.maze[0][13].northWall=0;
    sim_maze.maze[1][13].westWall=1;sim_maze.maze[1][13].northWall=1;
    sim_maze.maze[2][13].westWall=0;sim_maze.maze[2][13].northWall=0;
    sim_maze.maze[3][13].westWall=0;sim_maze.maze[3][13].northWall=1;
    sim_maze.maze[4][13].westWall=0;sim_maze.maze[4][13].northWall=1;
    sim_maze.maze[5][13].westWall=0;sim_maze.maze[5][13].northWall=1;
    sim_maze.maze[6][13].westWall=0;sim_maze.maze[6][13].northWall=1;
    sim_maze.maze[7][13].westWall=0;sim_maze.maze[7][13].northWall=1;
    sim_maze.maze[8][13].westWall=0;sim_maze.maze[8][13].northWall=1;
    sim_maze.maze[9][13].westWall=1;sim_maze.maze[9][13].northWall=0;

    sensor_copy_sim();
   
}

