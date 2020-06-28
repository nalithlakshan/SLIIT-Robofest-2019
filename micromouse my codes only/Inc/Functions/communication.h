#ifndef COMMUNICATION_H_
#define COMMUNICATION_H_

void print(char *msg,...){

	char buff[80];
	va_list args;
	va_start(args,msg);
	vsprintf(buff,msg,args);

	for (int i =0 ; i < strlen(buff); i++){
		//HAL_UART_Transmit(&huart1, buff[i], 1, 100);
		USART1->DR =buff[i];
		while(!(USART1->SR & USART_SR_TXE));
	}
}

//Use this for HAL UART
//uint8_t data=0xAA;
//HAL_UART_Transmit(&huart1, &data, 1, 100);



/*###############################Buzzer#############################*/
void beep(int duration){
	buzzerTime = duration;
	HAL_GPIO_WritePin(BUZZER_GPIO_Port, BUZZER_Pin, 1);
}


/*#######################Seven Segment Display#########################*/

void display_0(){
	HAL_GPIO_WritePin(BCD_A_GPIO_Port, BCD_A_Pin, 0);
	HAL_GPIO_WritePin(BCD_B_GPIO_Port, BCD_B_Pin, 0);
	HAL_GPIO_WritePin(BCD_C_GPIO_Port, BCD_C_Pin, 0);
	HAL_GPIO_WritePin(BCD_D_GPIO_Port, BCD_D_Pin, 0);
}

void display_1(){
	HAL_GPIO_WritePin(BCD_A_GPIO_Port, BCD_A_Pin, 1);
	HAL_GPIO_WritePin(BCD_B_GPIO_Port, BCD_B_Pin, 0);
	HAL_GPIO_WritePin(BCD_C_GPIO_Port, BCD_C_Pin, 0);
	HAL_GPIO_WritePin(BCD_D_GPIO_Port, BCD_D_Pin, 0);
}

void display_2(){
	HAL_GPIO_WritePin(BCD_A_GPIO_Port, BCD_A_Pin, 0);
	HAL_GPIO_WritePin(BCD_B_GPIO_Port, BCD_B_Pin, 1);
	HAL_GPIO_WritePin(BCD_C_GPIO_Port, BCD_C_Pin, 0);
	HAL_GPIO_WritePin(BCD_D_GPIO_Port, BCD_D_Pin, 0);
}

void display_3(){
	HAL_GPIO_WritePin(BCD_A_GPIO_Port, BCD_A_Pin, 1);
	HAL_GPIO_WritePin(BCD_B_GPIO_Port, BCD_B_Pin, 1);
	HAL_GPIO_WritePin(BCD_C_GPIO_Port, BCD_C_Pin, 0);
	HAL_GPIO_WritePin(BCD_D_GPIO_Port, BCD_D_Pin, 0);
}

void display_4(){
	HAL_GPIO_WritePin(BCD_A_GPIO_Port, BCD_A_Pin, 0);
	HAL_GPIO_WritePin(BCD_B_GPIO_Port, BCD_B_Pin, 0);
	HAL_GPIO_WritePin(BCD_C_GPIO_Port, BCD_C_Pin, 1);
	HAL_GPIO_WritePin(BCD_D_GPIO_Port, BCD_D_Pin, 0);
}

void display_5(){
	HAL_GPIO_WritePin(BCD_A_GPIO_Port, BCD_A_Pin, 1);
	HAL_GPIO_WritePin(BCD_B_GPIO_Port, BCD_B_Pin, 0);
	HAL_GPIO_WritePin(BCD_C_GPIO_Port, BCD_C_Pin, 1);
	HAL_GPIO_WritePin(BCD_D_GPIO_Port, BCD_D_Pin, 0);
}

void display_6(){
	HAL_GPIO_WritePin(BCD_A_GPIO_Port, BCD_A_Pin, 0);
	HAL_GPIO_WritePin(BCD_B_GPIO_Port, BCD_B_Pin, 1);
	HAL_GPIO_WritePin(BCD_C_GPIO_Port, BCD_C_Pin, 1);
	HAL_GPIO_WritePin(BCD_D_GPIO_Port, BCD_D_Pin, 0);
}

void display_7(){
	HAL_GPIO_WritePin(BCD_A_GPIO_Port, BCD_A_Pin, 1);
	HAL_GPIO_WritePin(BCD_B_GPIO_Port, BCD_B_Pin, 1);
	HAL_GPIO_WritePin(BCD_C_GPIO_Port, BCD_C_Pin, 1);
	HAL_GPIO_WritePin(BCD_D_GPIO_Port, BCD_D_Pin, 0);
}

void display_8(){
	HAL_GPIO_WritePin(BCD_A_GPIO_Port, BCD_A_Pin, 0);
	HAL_GPIO_WritePin(BCD_B_GPIO_Port, BCD_B_Pin, 0);
	HAL_GPIO_WritePin(BCD_C_GPIO_Port, BCD_C_Pin, 0);
	HAL_GPIO_WritePin(BCD_D_GPIO_Port, BCD_D_Pin, 1);
}

void display_9(){
	HAL_GPIO_WritePin(BCD_A_GPIO_Port, BCD_A_Pin, 1);
	HAL_GPIO_WritePin(BCD_B_GPIO_Port, BCD_B_Pin, 0);
	HAL_GPIO_WritePin(BCD_C_GPIO_Port, BCD_C_Pin, 0);
	HAL_GPIO_WritePin(BCD_D_GPIO_Port, BCD_D_Pin, 1);
}

void display_off(){
	HAL_GPIO_WritePin(BCD_A_GPIO_Port, BCD_A_Pin, 1);
	HAL_GPIO_WritePin(BCD_B_GPIO_Port, BCD_B_Pin, 1);
	HAL_GPIO_WritePin(BCD_C_GPIO_Port, BCD_C_Pin, 1);
	HAL_GPIO_WritePin(BCD_D_GPIO_Port, BCD_D_Pin, 1);
}

#endif

