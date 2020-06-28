#ifndef SENSOR_FUNCTION_H_
#define SENSOR_FUNCTION_H_

void panel(){
	//Read DC value
	LF_RECEIVER_READ
	RF_RECEIVER_READ
	L_RECEIVER_READ
	R_RECEIVER_READ
	int LFvalue_EmitterOFF	=LFvalue;
	int RFvalue_EmitterOFF	=RFvalue;
	int Lvalue_EmitterOFF	=Lvalue;
	int Rvalue_EmitterOFF	=Rvalue;

	//Left Front Sensor
	LF_EMITTER_ON
	DWT_Delay_us(60);
	LF_RECEIVER_READ
	LFvalue=LFvalue-LFvalue_EmitterOFF;
	LF_EMITTER_OFF
	if(LFvalue<0)
		LFvalue=0;
	DWT_Delay_us(80);

	//Right Front Sensor
	RF_EMITTER_ON
	DWT_Delay_us(60);
	RF_RECEIVER_READ
	RFvalue=RFvalue-RFvalue_EmitterOFF;
	RF_EMITTER_OFF
	if(RFvalue<0)
		RFvalue=0;
	DWT_Delay_us(80);

	//Diagonal Sensors
	DIAGONAL_EMITTER_ON
	DWT_Delay_us(60);
	L_RECEIVER_READ
	R_RECEIVER_READ
	Lvalue=Lvalue-Lvalue_EmitterOFF;
	Rvalue=Rvalue-Rvalue_EmitterOFF;
	DIAGONAL_EMITTER_OFF
	if(Lvalue<0)
		Lvalue=0;
	if(Rvalue<0)
		Rvalue=0;
	DWT_Delay_us(80);

	Lvalue	=Lvalue*reflectionRateSide/1000.0;
	Rvalue	=Rvalue*reflectionRateSide/1000.0;
	RFvalue	=RFvalue*reflectionRateFront/1000.0;
	LFvalue	=LFvalue*reflectionRateFront/1000.0;

	VOLMETER_READ
	if((volMeter<2900)&&(volMeter>1500)){
		//beep(5000);
	}
	#ifdef PANEL_PRINT
	print("%4d   %4d   %4d   %4d   %4d  %d\n\r",LFvalue,Lvalue,Rvalue,RFvalue,0,4096);
	#endif
}

#endif
