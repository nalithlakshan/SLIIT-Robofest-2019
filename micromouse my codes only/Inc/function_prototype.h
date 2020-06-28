void main_loop();
void setup();
//Use as printf to get a serial print
void print(char *msg,...);


//Sensor panel read and update the values
void panel();

//Motor Funtions
void straight(int speed);
void gyroStraight(int speed);
void reverse(int speed);
void brake();
void neutral();

//Wall Following Functions
void wallfollow(int speed);
void Both_wallfollow(int speed);
void Left_wallfollow(int speed);
void Right_wallfollow(int speed);
void wallfollow_known_walls(int speed);
void speedadjust(int speed);

//turns
void rotateLeft(int speed);
void rotateRight(int speed);
void turnLeft(int angle);
void turnRight(int angle);
void turnRight90();
void turnLeft90();
void turnRight180();
void turnLeft180();
void curve90Left();
void curve90Right();

void frontWallAlign(int speed);
void stopEnd();
void edge2center_without_brake();
void edge2center_with_brake();

//Seven Segment Displays
void display_0();
void display_1();
void display_2();
void display_3();
void display_4();
void display_5();
void display_6();
void display_7();
void display_8();
void display_9();
void display_off();

//Buzzer
void beep(int duration);
void buzzerSetDuty(int duty);
void buzzerSetFrequency(int freq);

//PID
void resetRelativeAngle();
void update_relativeAngleArray();
int get_relativeAngle();
void getSensorEror();


void finalFunction();
