void setup(){
	print("Starting MCU!!!!!!!!!!!!!!!!!!!!!!!!!!");

	HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_3);
	HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_4);


	//#define PANEL_PRINT
	//#define WALL_FOLLOW_MODE_DEBUG
	//#define WALL_DETECTION_AT_EDGE_DEBUG
	//#define PRINTING_MAZE_ON_RUN_MODE
	//#define SENSOR_ERROR_DEBUG

	DWT_Delay_Init ();

	Lcount=0;
	Rcount=0;

	display_off();

	setup_run();

	setupGyro(1);
	HAL_Delay(250);




	resetAngle();
	resetRelativeAngle();





}
