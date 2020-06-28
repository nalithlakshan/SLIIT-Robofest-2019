#ifndef MAINPID_H_
#define MAINPID_H_

void resetRelativeAngle(){
	for(int i=0; i<600; i++){
		relativeAngleArray[i] = 0.0;
	}
	relativeAngle = 0;
//	memset(&relativeAngleArray,0,sizeof(relativeAngleArray));
}

void update_relativeAngleArray(){
	relativeAngleArray[bufferPtr] = getDsp()*0.005;
	bufferPtr++;
	if(bufferPtr==600){
		bufferPtr = 0;
	}

}

int get_relativeAngle(){
	relativeAngle = 0;
	for(int i=0; i<600; i++){
		relativeAngle += relativeAngleArray[i];
	}
	return (int) relativeAngle;
}


void getSensorEror(void)//the very basic case
{
	//These 2 should only be used to E->C
	//E->C , C->E flags
	//int isLeftWallAvailable = MazeHasAWallRelative(&maze, state.pos.x, state.pos.y, state.pos.forwardDirection, LEFT);
	//int isRightWallAvailable = MazeHasAWallRelative(&maze, state.pos.x, state.pos.y, state.pos.forwardDirection, RIGHT);
	if(enCount<150 || (enCount<edge2center_count && enCount >(edge2center_count-50)))
		enchFlag = C2N_region;
	else
		enchFlag = N2C_region;

	if(enchFlag == C2N_region)
		sensorError = 0;
	else if(Lvalue > wallDetectionLevel && Rvalue < wallDetectionLevel)
		sensorError = Lvalue - threshold;
	else if(Lvalue < wallDetectionLevel && Rvalue > wallDetectionLevel)
		sensorError = threshold - Rvalue;
//	else if(Lvalue > wallDetectionLevel && Rvalue > wallDetectionLevel){
//		if(Lvalue>Rvalue)
//			sensorError = Lvalue - threshold;
//		else
//			sensorError = threshold - Rvalue;
//	}
	else if(Lvalue>wallLostLevel && Rvalue<wallLostLevel)
		sensorError = (Lvalue - threshold)/1;    //3
	else if(Rvalue>wallLostLevel && Lvalue<wallLostLevel)
		sensorError = (threshold - Rvalue)/1;    //3
	else
		sensorError = 0;

	#ifdef SENSOR_ERROR_DEBUG
	print("L:%d    R:%d    SenorErr:%d\n",Lvalue,Rvalue,sensorError);
	#endif
}



#endif
