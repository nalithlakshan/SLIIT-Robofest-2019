#ifndef MOTOR_FUNCTIONS_H_
#define MOTOR_FUNCTIONS_H_



void wallfollow(int speed){
	int TH=1600;
	if((Lvalue>TH)&&(Rvalue>TH)){
			Both_wallfollow(speed);
			#ifdef WALL_FOLLOW_MODE_DEBUG
			display_2();
			#endif
		}
		else if((Lvalue<TH)&&(Rvalue>TH)){
			Right_wallfollow(speed);
			#ifdef WALL_FOLLOW_MODE_DEBUG
			display_3();
			#endif
		}
		else if((Lvalue>TH)&&(Rvalue<TH)){
			Left_wallfollow(speed);
			#ifdef WALL_FOLLOW_MODE_DEBUG
			display_1();
			#endif
		}
		else{
			straight(speed);
			display_0();
		}
}


void wallfollow_known_walls(int speed){
	int isLeftWallAvailable = MazeHasAWallRelative(&maze, state.pos.x, state.pos.y, state.pos.forwardDirection, LEFT);
	int isRightWallAvailable = MazeHasAWallRelative(&maze, state.pos.x, state.pos.y, state.pos.forwardDirection, RIGHT);
	//int isFrontWallAvailable = MazeHasAWallRelative(&maze, state.pos.x, state.pos.y, state.pos.forwardDirection, FORWARD);

	if(isLeftWallAvailable && isRightWallAvailable){
		Both_wallfollow(speed);
	 }
	else if(isRightWallAvailable){
		Right_wallfollow(speed);
	}
	else if(isLeftWallAvailable){
		Left_wallfollow(speed);
	}
	else{
		gyroStraight(speed);
	}
}



void Both_wallfollow(int speed){
  error=Lvalue-Rvalue;
  float Kp=0.04; float Kd=1.5;
  float adjustment=Kp*error+Kd*(error-lasterror);
  if(adjustment>35){
    adjustment=35;
  }
  if(adjustment<(-35)){
    adjustment=-35;
  }
  pwmL=speed +adjustment;
  pwmR=speed -adjustment;

  speedadjust(speed);

  LPWMA(pwmL);
  LPWMB(0);
  RPWMA(pwmR);
  RPWMB(0);

  lasterror=error;
}




void Left_wallfollow(int speed){
  error=Lvalue-threshold;
  float Kp=0.1; float Kd=1.5;
  float adjustment=Kp*error+Kd*(error-lasterror);
  if(adjustment>35){
    adjustment=35;
  }
  if(adjustment<(-35)){
    adjustment=-35;
  }
  pwmL=speed +adjustment;
  pwmR=speed -adjustment;

  speedadjust(speed);

  //Serial.print(pwmL); Serial.print(" "); Serial.println(pwmR);
  LPWMA(pwmL);
  LPWMB(0);
  RPWMA(pwmR);
  RPWMB(0);

  lasterror=error;
}






void Right_wallfollow(int speed){
error=threshold-Rvalue;
  float Kp=0.035; float Kd=1.5;
  float adjustment=Kp*error+Kd*(error-lasterror);
  if(adjustment>35){
    adjustment=35;
  }
  if(adjustment<(-35)){
    adjustment=-35;
  }
  pwmL=speed +adjustment;
  pwmR=speed -adjustment;

  speedadjust(speed);

  //Serial.print(pwmL); Serial.print(" "); Serial.println(pwmR);
  LPWMA(pwmL);
  LPWMB(0);
  RPWMA(pwmR);
  RPWMB(0);

  lasterror=error;
}



void speedadjust(int speed){
    if(pwmL<speed-35){
    if(speed-35<0){
      pwmL=0;
    }
    else{
    pwmL=speed-35;
    }
  }
  if(pwmL>speed+35){
    if(speed+35<0){
      pwmL=0;
    }
    else{
    pwmL=speed+35;
    }
  }
  if(pwmR<speed-35){
    if(speed-35<0){
      pwmR=0;
    }
    else{
    pwmR=speed-35;
    }
  }
  if(pwmR>speed+35){
    if(speed+35<0){
      pwmR=0;
    }
    else{
    pwmR=speed+35;
    }
  }
}




#endif
