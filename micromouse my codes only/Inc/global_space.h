#ifndef GLOBAL_SPACE_H
#define GLOBAL_SPACE_H

//ADC1
ADC_ChannelConfTypeDef sConfig = {0};

//IR Receiver readings
int Lvalue	=0;
int LFvalue=0;
int Rvalue	=0;
int RFvalue=0;
int reflectionRateSide=900;
int reflectionRateFront=1000;
int volMeter=3000;

//IR receiver parameters
int pwmbase=220; int pwmL; int pwmR; float error; float lasterror;
int threshold=1700; int endintensity=2800
; //3600
int wallDetectionLevel=2000;
int wallLostLevel=600;

//Encoder parameters
int center2edge_count=270;
int center2center_count = 1050;
int edge2center_count = 730;  //1050-(270+50)
int edge2curveturn_count=430;
int curveturn2edge_count=100;
int curveturn_count=810;

int brakeDrift =100;
int brakeDelay =150;
int accelFactor =0;

//flags
int enchFlag = 0;
int stateFlag = 0;
int accelFlag = 1;

//Encoder Interrupts
uint32_t Lcount=0;
uint32_t Rcount=0;

//buzzer
int buzzerTime=0;

//Systick
int systickTime=0;

//PID related
float relativeAngleArray[600];
float relativeAngle = 0;
int bufferPtr=0;

int sensorError=0;

//Wall detection

//buttons
int buttonCounter=0;
int buttonState=0;
int initialDirectionCounter=0;

#endif
