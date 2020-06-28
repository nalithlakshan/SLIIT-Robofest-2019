#ifndef BASIC_MOTIONS_H_
#define BASIC_MOTIONS_H_


void straight(int speed){
	LPWMA(speed);
	LPWMB(0);
	RPWMA(speed);
	RPWMB(0);
}


void gyroStraight(int speed){
	panel();
	getSensorEror();

  error = get_relativeAngle()*50 + sensorError*1;
 // error = (angle+angleConst)*50 + sensorError*1;

  float Kp=0.1; float Kd=1.5;                //5,30 for gyro   float Kp=0.1; float Kd=1.5;
  float adjustment=Kp*error+Kd*(error-lasterror);

  if(adjustment>35){
	adjustment=35;
  }
  if(adjustment<(-35)){
	adjustment=-35;
  }

  pwmL=speed +adjustment;
  pwmR=speed -adjustment;

  //speedadjust(speed);
  if(pwmL>255)
	  pwmL = 255;
  if(pwmL<0)
	  pwmL = 0;
  if(pwmR>255)
	  pwmR = 255;
  if(pwmR<0)
	  pwmR = 0;

  LPWMA(pwmL);
  LPWMB(0);
  RPWMA(pwmR);
  RPWMB(0);

  lasterror=error;

}


void reverse(int speed){
	LPWMA(0);
	LPWMB(speed);
	RPWMA(0);
	RPWMB(speed);
}

void brake(){
	LPWMA(255);
	LPWMB(255);
	RPWMA(255);
	RPWMB(255);
	accelFlag = 1;
}

void neutral(){
	LPWMA(0);
	LPWMB(0);
	RPWMA(0);
	RPWMB(0);
}

void rotateLeft(int speed){
	LPWMA(0);
	LPWMB(speed);
	RPWMA(speed);
	RPWMB(0);
}

void rotateRight(int speed){
	LPWMA(speed);
	LPWMB(0);
	RPWMA(0);
	RPWMB(speed);
}

void turnLeft(int angle){
	int requiredCount=(3.83*angle);
	Lcount=0;
	Rcount=0;
	int instantaneousSpeed=130;
	//int maxSpeed=130;
	while(enCount<requiredCount){
		loopStart
		if(enCount<requiredCount/2){
//			if(instantaneousSpeed<maxSpeed){
//				instantaneousSpeed++;
//			}

			instantaneousSpeed=130+10*enCount/requiredCount/2;
		}
		else if(enCount>requiredCount/2){
//			if(instantaneousSpeed>100){
//				instantaneousSpeed-=5;
//			}
			instantaneousSpeed=110-20*(enCount-requiredCount/2)/requiredCount/2;
		}
		rotateLeft(instantaneousSpeed);
		//print("L:%3d  R:%3d \n",Lcount,Rcount);
		loopEnd
	}
	brake();
}

void turnRight(int angle){
	int requiredCount=(3.83*angle);
	Lcount=0;
	Rcount=0;
	int instantaneousSpeed=130;
	//int maxSpeed=130;
	while(enCount<requiredCount){
		loopStart
		if(enCount<requiredCount/2){
//			if(instantaneousSpeed<maxSpeed){
//				instantaneousSpeed++;
//			}

			instantaneousSpeed=130+10*enCount/requiredCount/2;
		}
		else if(enCount>requiredCount/2){
//			if(instantaneousSpeed>100){
//				instantaneousSpeed-=5;
//			}
			instantaneousSpeed=110-20*(enCount-requiredCount/2)/requiredCount/2;
		}
		rotateRight(instantaneousSpeed);
		//print("L:%3d  R:%3d \n",Lcount,Rcount);
		loopEnd
	}
	brake();
}

void frontWallAlign(int speed){

	error=RFvalue-LFvalue;
	float Kp=0.08; float Kd=1.5;
	float adjustment=Kp*error+Kd*(error-lasterror);
	if(adjustment>50){
	adjustment=50;
	}
	if(adjustment<(-50)){
	adjustment=-50;
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

void stopEnd(){
	int speed = pwmbase;
	panel();
	while((LFvalue+RFvalue)<endintensity*2){
		frontWallAlign(speed);
		speed=120-40*((LFvalue+RFvalue)/2)/endintensity;
//		if(speed<60){
//			speed=60;
//		}
		panel();
	}
	brake();
}


void edge2center_without_brake(){
	Lcount=(enCount-(center2edge_count+50))/2;
	Rcount=Lcount;
	while(enCount<edge2center_count){
		loopStart
		//panel();
		//wallfollow_known_walls(pwmbase);
		gyroStraight(pwmbase);
		loopEnd
	}
}

void edge2center_with_brake(){
	Lcount=(enCount-(center2edge_count+50))/2;
	Rcount=Lcount;
	int speed=pwmbase;
	while(enCount<(edge2center_count-brakeDrift)){
		loopStart
		//panel();
		speed=180-40*enCount/edge2center_count;
		//wallfollow_known_walls(speed);
		gyroStraight(speed);
		loopEnd
	}
	brake();
}


void turnRight90(){
	turnRight(90);
	MousePositionRotateRight(&(state.pos));
	HAL_Delay(brakeDelay);
	resetRelativeAngle();
	angleConst+=90;
}


void turnLeft90(){
	turnLeft(90);
	MousePositionRotateLeft(&(state.pos));
	HAL_Delay(brakeDelay);
	resetRelativeAngle();
	angleConst-=90;
}

void turnRight180(){
	turnRight(189);
	MousePositionRotateBackwards(&(state.pos));
	HAL_Delay(brakeDelay);
	resetRelativeAngle();
	angleConst+=180;
}

void turnLeft180(){
	turnLeft(190);
	MousePositionRotateBackwards(&(state.pos));
	HAL_Delay(brakeDelay);
	resetRelativeAngle();
	angleConst-=180;
}


void curve90Left(){
	Lcount=0;
	Rcount=0;
	while(enCount<edge2curveturn_count){
		loopStart
		gyroStraight(130);
		loopEnd
	}
	LPWMA(255);
	LPWMB(255);
	Rcount=0;
	while(Rcount<curveturn_count){
		RPWMA(130);
		RPWMB(0);
	}
	MousePositionRotateLeft(&(state.pos));

	//Curve Turn End to the Edge
	Lcount=0;
	Rcount=0;
	while(enCount<curveturn2edge_count){
		loopStart
		gyroStraight(130);
		loopEnd
	}

}



void curve90Right(){
	Lcount=0;
	Rcount=0;
	while(enCount<edge2curveturn_count){
		loopStart
		gyroStraight(130);
		loopEnd
	}
	RPWMA(255);
	RPWMB(255);
	Lcount=0;
	while(Lcount<curveturn_count){
		LPWMA(130);
		LPWMB(0);
	}
	MousePositionRotateRight(&(state.pos));

	//Curve Turn End to the Edge
	Lcount=0;
	Rcount=0;
	while(enCount<curveturn2edge_count){
		loopStart
		gyroStraight(130);
		loopEnd
	}

}

#endif
