
/*************************
    L3G4200D Registers
*************************/
#define WHO_AM_I 0x0F
#define CTRL_REG1 0x20
#define CTRL_REG2 0x21
#define CTRL_REG3 0x22
#define CTRL_REG4 0x23
#define CTRL_REG5 0x24
#define REFERENCE 0x25
#define OUT_TEMP 0x26
#define STATUS_REG 0x27
#define OUT_X_L 0x28
#define OUT_X_H 0x29
#define OUT_Y_L 0x2A
#define OUT_Y_H 0x2B
#define OUT_Z_L 0x2C
#define OUT_Z_H 0x2D
#define FIFO_CTRL_REG 0x2E
#define FIFO_SRC_REG 0x2F
#define INT1_CFG 0x30
#define INT1_SRC 0x31
#define INT1_TSH_XH 0x32
#define INT1_TSH_XL 0x33
#define INT1_TSH_YH 0x34
#define INT1_TSH_YL 0x35
#define INT1_TSH_ZH 0x36
#define INT1_TSH_ZL 0x37
#define INT1_DURATION 0x38

#define byte uint8_t
#define HIGH 1
#define LOW 0

// globle vartiables
uint16_t zCal=0;
float angle=0;
long int lastTime=0;
float angleConst=0;
//--------------------

// function prototypes
uint8_t readRegister(byte address);
void writeRegister(byte address,byte data);
int setupGyro(byte fullScale);
int getGyroValue(void);
float getDsp(void);
void calibarateGyro(void);
float getAngle(void);
void resetAngle(void);
int isGyroUpdated(void);
//--------------------

//functions

uint8_t readRegister(byte address){

	uint8_t buff[2];
	buff[0]=address|0x80;
	buff[1]=0xff;
	//read data
	  //activate spi bus
	  HAL_GPIO_WritePin(CS_GPIO_Port, CS_Pin, LOW);
	  // transmit register address

	  HAL_SPI_Transmit(&hspi2, buff , 1, 10);
	  // receive data
	  HAL_SPI_Receive(&hspi2, &buff[1], 1, 10);
	  //desable spi bus
	  HAL_GPIO_WritePin(CS_GPIO_Port, CS_Pin, HIGH);

	return buff[1];
}

void writeRegister(byte address,byte data){

	uint8_t buff[2];
	buff[0]=address;
	buff[1]=data;
	//read data
	  //activate spi bus
	  HAL_GPIO_WritePin(CS_GPIO_Port, CS_Pin, LOW);
	  // transmit register address
	  // transmit the data
	  HAL_SPI_Transmit(&hspi2, buff , 2, 10);

	  //desable spi bus
	  HAL_GPIO_WritePin(CS_GPIO_Port, CS_Pin, HIGH);

}

int setupGyro(byte fullScale)
  // 0: 250 dps
  // 1: 500 dps
  // 2: 2000 dps
{
  // Let's first check that we're communicating properly
  // The WHO_AM_I register should read 0xD3
  if(readRegister(WHO_AM_I)!=0xD3)
    return -1;

  // Enable x, y, z and turn off power down:
  writeRegister(CTRL_REG1, 0b10001100);

  // If you'd like to adjust/use the HPF, you can edit the line below to configure CTRL_REG2:
  writeRegister(CTRL_REG2, 0b00000000);

  // Configure CTRL_REG3 to generate data ready interrupt on INT2
  // No interrupts used on INT1, if you'd like to configure INT1
  // or INT2 otherwise, consult the datasheet:
  writeRegister(CTRL_REG3, 0b00001000);

  // CTRL_REG4 controls the full-scale range, among other things:
  fullScale &= 0x03;
  writeRegister(CTRL_REG4, fullScale<<4);

  // CTRL_REG5 controls high-pass filtering of outputs, use it
  // if you'd like:
  writeRegister(CTRL_REG5, 0b00000000);

  return 1;
}

int isGyroUpdated(void){
	if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_12)==1){
		return 1;
	}
	else{
		return 0;
	}
}

int getGyroValue(void)
{
  //int x, y, z;
  int16_t z;
  /*
  x = (readRegister(0x29)&0xFF)<<8;
  x |= (readRegister(0x28)&0xFF);

  y = (readRegister(0x2B)&0xFF)<<8;
  y |= (readRegister(0x2A)&0xFF);
  */

  z = (readRegister(0x2D)&0xFF)<<8;
  z |= (readRegister(0x2C)&0xFF);

  return z;
}

void calibarateGyro(void){
	int cal=0;
	for (int i =0;i<100;i++){

		cal+= (int)getGyroValue();
	}
	zCal=cal/100;
}

float getDsp(void){

	int16_t rawValue = getGyroValue();
	if((-50<rawValue)&(rawValue<50))
		rawValue=0;
	float dsp= ((float)(rawValue)-0.55)*17.5/1000;
	return dsp;
}

// call this function to calculate the current angle;
float getAngle(void){
	angle += getDsp()*(HAL_GetTick()-lastTime)/1000;
	lastTime= HAL_GetTick();
	return angle;
}

// call this for set the initial angle to zero
void resetAngle(void){
	angle=0;
	lastTime=HAL_GetTick();
}
