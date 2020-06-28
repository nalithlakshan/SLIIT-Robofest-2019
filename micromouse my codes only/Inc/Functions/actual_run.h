#ifndef ACTUAL_RUN_H_
#define ACTUAL_RUN_H_

/* set_target_home() , set_target_center() , setup_run() <-- These are already
 * there in the simulation.h file
 */



void finalFunction(){

	while(1){

		if(HAL_GPIO_ReadPin(BUTTON1_GPIO_Port, BUTTON1_Pin) == 0){
			HAL_Delay(600);
			buttonCounter++;
		}
		buttonState = buttonCounter % 5;

		if(buttonState == 0){
			display_1();
			pwmbase = 180;
			brakeDrift =100;
			endintensity=2800;
		}
		else if(buttonState == 1){
			display_2();
			pwmbase = 180;
			brakeDrift =100;
			endintensity=3200;
		}
		else if(buttonState == 2){
			display_3();
			pwmbase = 180;
			brakeDrift =50;
			endintensity=3000;
		}
		else if(buttonState == 3){
			display_4();
			pwmbase = 220;
			brakeDrift =100;
			endintensity=2800;
		}
		else if(buttonState == 4){
			display_5();
			pwmbase = 160;
			brakeDrift =50;
			endintensity=3200;
		}


		if(HAL_GPIO_ReadPin(BUTTON2_GPIO_Port, BUTTON2_Pin) == 0){
			HAL_Delay(600);
			initialDirectionCounter++;
		}

		if((initialDirectionCounter % 2) == 0){
			MousePositionInit(&state.pos,EAST,0,13);
			HAL_GPIO_WritePin(LED5_GPIO_Port, LED5_Pin, 0);
		}
		else{
			MousePositionInit(&state.pos,NORTH,0,13);
			HAL_GPIO_WritePin(LED5_GPIO_Port, LED5_Pin, 1);
		}

		panel();
		if(LFvalue>2000){
			break;
		}

	}

	HAL_GPIO_WritePin(LED5_GPIO_Port, LED5_Pin, 0);

	MazeSetWallRelative(&maze,state.pos.x, state.pos.y, 1,state.pos.forwardDirection, LEFT);
	MazeSetWallRelative(&maze,state.pos.x, state.pos.y, 1,state.pos.forwardDirection, RIGHT);


	beep(30);HAL_Delay(60);
	beep(30);HAL_Delay(60);
	beep(30);HAL_Delay(60);
	beep(30);HAL_Delay(60);
	beep(30);HAL_Delay(60);
	beep(30);HAL_Delay(60);
	beep(30);HAL_Delay(60);
	beep(30);HAL_Delay(60);
	beep(30);HAL_Delay(60);
	beep(30);HAL_Delay(60);
	beep(30);HAL_Delay(60);
	beep(30);HAL_Delay(60);
	beep(500);HAL_Delay(500);


	run_in_maze();

}














void run_in_maze(){
	int number_of_moves=0;
	set_target_center();
	SimpleFloodFillSolve(&flood);

	while(MazeGetDistance(&maze, state.pos.x, state.pos.y)!=0)
	{
		center2edge_actions();
		beep(100);
//		display_1();

		edge2center_actions();
//		display_2();

	#ifdef PRINTING_MAZE_ON_RUN_MODE
	brake();
	print_mouse_position();
	MazePrint(&maze,4,4);
	HAL_Delay(1000);
	#endif
	number_of_moves++;

	}

	brake();
	HAL_Delay(5000);

	//print("No of move to center: %d\n",number_of_moves);



	number_of_moves=0;
	set_target_home();
	SimpleFloodFillSolve(&flood);

	while(MazeGetDistance(&maze, state.pos.x, state.pos.y)!=0)
	{
		center2edge_actions();
		beep(100);
	//	display_1();

		edge2center_actions();
	//	display_2();

		#ifdef PRINTING_MAZE_ON_RUN_MODE
		brake();
		print_mouse_position();
		MazePrint(&maze,4,4);
		HAL_Delay(500);
		#endif

		number_of_moves++;

	}

	brake();
	HAL_Delay(5000);


//		number_of_moves=0;
//				set_target_center();
//				SimpleFloodFillSolve(&flood);
//				while(MazeGetDistance(&maze, state.pos.x, state.pos.y)!=0){
//					center2edge_actions();
//					beep(100);
//					display_1();
//
//					edge2center_actions();
//					beep(200);
//					display_2();
//					#ifdef PRINTING_MAZE_ON_RUN_MODE
//					print_mouse_position();
//					MazePrint(&maze,4,4);
//					#endif
//					number_of_moves++;
//
//				}
//				brake();
//				HAL_Delay(5000);
}


void center2edge_actions(){

	MousePositionGoForward(&(state.pos));
	maze.maze[state.pos.x][state.pos.y].explored=1;

	Lcount=0;
	Rcount=0;
	//resetAngle();
	while(enCount<center2edge_count){
		loopStart
		panel();
		if(accelFlag == 1){
			accelFactor = 20;
			accelFlag = 0;
		}
		gyroStraight(pwmbase - accelFactor);
		loopEnd
	}

	int number_of_Samples=0;
	int Lsum=0;
	int Rsum=0;
	int Fsum=0;

	while(enCount<(center2edge_count+50)){
		loopStart
		panel();
		gyroStraight(pwmbase);
		Lsum+=Lvalue;
		Rsum+=Rvalue;
		Fsum+=Fvalue;
		number_of_Samples++;
		loopEnd
	}

	int Lvalue_avg=Lsum/number_of_Samples;
	int Rvalue_avg=Rsum/number_of_Samples;
	int Fvalue_avg=Fsum/number_of_Samples;

	#ifdef WALL_DETECTION_AT_EDGE_DEBUG
	int L=0; int F=0; int R=0; //for debugging purposes
	#endif

	if (Lvalue_avg>600){   //500
		MazeSetWallRelative(&maze,state.pos.x, state.pos.y, 1,state.pos.forwardDirection, LEFT);
		#ifdef WALL_DETECTION_AT_EDGE_DEBUG
		L=1;
		#endif
	}

	if (Rvalue_avg>600){   //500
		MazeSetWallRelative(&maze,state.pos.x, state.pos.y, 1,state.pos.forwardDirection, RIGHT);
		#ifdef WALL_DETECTION_AT_EDGE_DEBUG
		R=1;
		#endif
	}

	if (Fvalue_avg>200){  //250
		MazeSetWallRelative(&maze,state.pos.x, state.pos.y, 1,state.pos.forwardDirection, FORWARD);
		#ifdef WALL_DETECTION_AT_EDGE_DEBUG
		F=1;
		#endif
	}

    #ifdef WALL_DETECTION_AT_EDGE_DEBUG
	print("Lvalue_avg=%4d L:%d   Fvalue_avg=%4d F:%d   Rvalue_avg=%4d R:%d ",
			Lvalue_avg, L, Fvalue_avg, F, Rvalue_avg, R);
	if(L==0 && F==0 && R==0)
		display_1();
	else if(L==0 && F==0 && R==1)
		display_2();
	else if(L==0 && F==1 && R==0)
		display_3();
	else if(L==0 && F==1 && R==1)
		display_4();
	else if(L==1 && F==0 && R==0)
		display_5();
	else if(L==1 && F==0 && R==1)
		display_6();
	else if(L==1 && F==1 && R==0)
		display_7();
	else if(L==1 && F==1 && R==1)
		display_8();
	#endif



	//update upcoming square to maze memory ???
	//MazeSetWallRelative(&maze,state.pos.x, state.pos.y, 1,NORTH, WEST);
	//MazeHasAWallRelative(Maze* this, int x, int y, Compass forwardDir, Direction relativeDir);      //<--for a fast run

}






void edge2center_actions(){
	SimpleFloodFillSolve(&flood);
	char Move= MoveGenGetNextMove(&maze, state.pos.x, state.pos.y, state.pos.forwardDirection);

	//print("%d\n",enCount);
    if (Move=='F'|| Move=='f'){
    		edge2center_without_brake();
    }


    else if (Move=='B'|| Move=='b'){
    	if(MazeHasAWallRelative(&maze, state.pos.x, state.pos.y, state.pos.forwardDirection, FORWARD)){
    		stopEnd();
    		HAL_Delay(brakeDelay);
    	}
    	else{
    		edge2center_with_brake();
    		HAL_Delay(brakeDelay);
    	}
    	panel();
    	if(Lvalue>Rvalue){
    		turnRight180();
    		HAL_Delay(brakeDelay);
    	}
    	else if(Lvalue<Rvalue){
    		turnLeft180();
    		HAL_Delay(brakeDelay);
    	}
    	else{
    		turnRight180();
    		HAL_Delay(brakeDelay);
    	}
    }


    else if (Move=='L'|| Move=='l'){
    	if(MazeHasAWallRelative(&maze, state.pos.x, state.pos.y, state.pos.forwardDirection, FORWARD)){
    		stopEnd();
    		HAL_Delay(brakeDelay);
    	}
    	else{
    		edge2center_with_brake();
    		HAL_Delay(brakeDelay);
    	}
    	turnLeft90();
    }


    else if (Move=='R'|| Move=='r'){
    	if(MazeHasAWallRelative(&maze, state.pos.x, state.pos.y, state.pos.forwardDirection, FORWARD)){
    		stopEnd();
    		HAL_Delay(brakeDelay);
    	}
    	else{
    		edge2center_with_brake();
    		HAL_Delay(brakeDelay);
    	}
    	turnRight90();
    }


}






#endif
