/*...............IR Emiiter Operations....................*/

#define DIAGONAL_EMITTER_ON \
	HAL_GPIO_WritePin(DIAGONAL_EMITTER_GPIO_Port,DIAGONAL_EMITTER_Pin,1);

#define DIAGONAL_EMITTER_OFF \
	HAL_GPIO_WritePin(DIAGONAL_EMITTER_GPIO_Port,DIAGONAL_EMITTER_Pin,0);

#define LF_EMITTER_ON \
	HAL_GPIO_WritePin(LF_EMITTER_GPIO_Port,LF_EMITTER_Pin,1);

#define LF_EMITTER_OFF \
	HAL_GPIO_WritePin(LF_EMITTER_GPIO_Port,LF_EMITTER_Pin,0);

#define RF_EMITTER_ON \
	HAL_GPIO_WritePin(RF_EMITTER_GPIO_Port,RF_EMITTER_Pin,1);

#define RF_EMITTER_OFF \
	HAL_GPIO_WritePin(RF_EMITTER_GPIO_Port,RF_EMITTER_Pin,0);




/*................IR Receiver Operations.........................*/


#define L_RECEIVER_READ \
	sConfig.Channel= ADC_CHANNEL_8;\
	HAL_ADC_ConfigChannel(&hadc1, &sConfig);\
	HAL_ADC_Start(&hadc1);\
	if(HAL_ADC_PollForConversion(&hadc1, 5)== HAL_OK){\
		Lvalue=HAL_ADC_GetValue(&hadc1);\
	}



#define LF_RECEIVER_READ \
	sConfig.Channel= ADC_CHANNEL_9;\
	HAL_ADC_ConfigChannel(&hadc1, &sConfig);\
	HAL_ADC_Start(&hadc1);\
	if(HAL_ADC_PollForConversion(&hadc1, 5)== HAL_OK){\
		LFvalue=HAL_ADC_GetValue(&hadc1);\
	}

#define RF_RECEIVER_READ sConfig.Channel= ADC_CHANNEL_4;\
	HAL_ADC_ConfigChannel(&hadc1, &sConfig);\
	HAL_ADC_Start(&hadc1);\
	if(HAL_ADC_PollForConversion(&hadc1, 5)== HAL_OK){ \
		RFvalue=HAL_ADC_GetValue(&hadc1);\
	}

#define R_RECEIVER_READ \
	sConfig.Channel= ADC_CHANNEL_5;\
	HAL_ADC_ConfigChannel(&hadc1, &sConfig);\
	HAL_ADC_Start(&hadc1);\
	if(HAL_ADC_PollForConversion(&hadc1, 5)== HAL_OK){\
		Rvalue=HAL_ADC_GetValue(&hadc1);\
	}

/*................Vol Meter Battery Check....................*/
#define VOLMETER_READ \
	sConfig.Channel = ADC_CHANNEL_3;\
	HAL_ADC_ConfigChannel(&hadc3, &sConfig);\
	HAL_ADC_Start(&hadc3);\
	if(HAL_ADC_PollForConversion(&hadc3, 5)== HAL_OK){\
		volMeter = HAL_ADC_GetValue(&hadc3);\
	}



/*................Motor PWM Operations.......................*/
#define LPWMA(x) htim4.Instance->CCR1=x;
#define LPWMB(x) htim4.Instance->CCR2=x;
#define RPWMB(x) htim4.Instance->CCR3=x;
#define RPWMA(x) htim4.Instance->CCR4=x;

/*................Constant Loop Time.......................*/
#define loopStart \
	uint32_t T1,T2;\
	T1=HAL_GetTick();\
	T2=HAL_GetTick();

#define loopEnd \
	T2=HAL_GetTick();\
	while(T2<(T1+2))\
	{\
		T2=HAL_GetTick();\
	}

/*...............Related to mouse movements.....................*/
#define enCount ((Lcount+Rcount)/2)
#define Fvalue ((LFvalue+RFvalue)/2)


/*......................Flag Values..............................*/
#define N2C_region 0
#define C2N_region 1

#define E2C_state 0
#define C2E_state 1
#define E2E_state 2
