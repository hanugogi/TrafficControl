#include<stdio.h>
#include<errno.h>
#include<string.h>
#include<stdbool.h>
#include<wiringPi.h>

//-----------------------------------------------

#define RED 100
#define ORANGE 101
#define GREEN 102

#define TL_L1 11	//Traffic Light Left
#define TL_L2 10
#define TL_R1 21	//Traffic Light Right
#define TL_R2 22

#define PTL_L_F 25	//Pedestrian Traffic Light Left Front
#define PTL_L_B 27	//Pedestrian Traffic LIght Left Backward
#define PTL_R_F 8	//Pedestrian Traffic Light Right Front
#define PTL_R_B	9	//Pedestrian Traffic Light Right Backward

#define IR_L1 28	//Left IRsensor For Car First
#define IR_L2 29	//Left IRsensor For Car Second
#define IR_R1 5		//Right IRsensor For Car First
#define IR_R2 4		//Right IRsensor For Car Second

#define IR_L_S 16	//Left Stop IRsensor
#define IR_R_S 13	//Right Stop IRsensor

#define PIR_L 15	//Left IRSensor For Pedestrian
#define PIR_R 14	//Right IRSensor For Pedestrian

#define DATA1 24	//Communication Data Pin 1
#define DATA2 25	//Communication Data Pin 2

#define GEAR1	1
#define GEAR2	2
#define STOP	0
#define TEST	3

//-----------------------------------------------

void Pin_Init(void);
void ISR_Init(void);

void ISR_IR1(void);
void ISR_IR2(void);
void ISR_IRStop(void);
void ISR_PIR(void);

void TrafficLights(char mode);
int SendData(char command);

//-----------------------------------------------

bool flag_speed = false;
bool flag_car = false;
bool flag_pedestrian = false;

static double speed;	//cm/s

//-----------------------------------------------

int main(void){
	char temp;

	if(wiringPiSetup() == -1){
		perror("wiringPi");
		return 1;
	}
	
	printf("Waiting...");
	temp = getchar();
	
	Pin_Init();
	ISR_Init();

	TrafficLights(GREEN);

	(temp == '2') ? printf("GEAR2\n", SendData(GEAR2)) : printf("GEAR1\n", SendData(GEAR1));

	while(1){};
}

//-----------------------------------------------

void Pin_Init(void){
	char pins[] = {TL_L1, TL_L2, TL_R1, TL_R2, PTL_L_F, PTL_L_B, PTL_R_F, PTL_R_B, IR_L1, IR_L2, IR_R1, IR_R2, PIR_L, PIR_R, DATA1, DATA2};

	for(int i = 0; i < strlen(pins); i++)
		pinMode(pins[i], OUTPUT);
	printf("PinMode All Set\n");
}

//-----------------------------------------------

void ISR_Init(void){
	wiringPiISR(IR_L1, INT_EDGE_RISING, ISR_IR1);
	wiringPiISR(IR_R1, INT_EDGE_RISING, ISR_IR1);

	wiringPiISR(IR_L2, INT_EDGE_RISING, ISR_IR2);
	wiringPiISR(IR_R2, INT_EDGE_RISING, ISR_IR2);


	wiringPiISR(IR_L_S, INT_EDGE_RISING, ISR_IRStop);
	wiringPiISR(IR_R_S, INT_EDGE_RISING, ISR_IRStop);


	wiringPiISR(PIR_L, INT_EDGE_RISING, ISR_PIR);
	wiringPiISR(PIR_R, INT_EDGE_RISING, ISR_PIR);

	printf("ISR All Set\n");
}

//-----------------------------------------------

void ISR_IR1(void){
	flag_car = true;
	printf("First IR Checked\n");

	int before, after, time;
	
	before = millis();
	
	while(!flag_speed){};
	printf(" Checked\n");

	after = millis();
	time = after - before;

	speed = 85/time;						//85mm / miliesecond
	speed *= 100;							//division 10 multiply 1000

	printf("Speed: %lf\ncm/s", speed);
	flag_speed = false;
}

//-----------------------------------------------

void ISR_IR2(void){
	flag_speed = true;
	printf("Second IR");
}

//-----------------------------------------------

void ISR_IRStop(void){
	SendData(STOP);
	printf("Stop IR Checked\n");
}

//-----------------------------------------------

void ISR_PIR(void){
	printf("Pedestrian IR Checked\n");
	double braking, max, count;

	if(!flag_pedestrian){
		for(int i = 0; i < 4700; i++){
			delay(1);
			if(flag_car) break;
		}
		flag_car = false;

		braking = (speed / 254) * speed;	//Get Braking Distance
		max = 51 - braking;					

		count = max / speed * 1000;
		delay(count);

		TrafficLights(ORANGE);
		delay(1000);

		TrafficLights(RED);
		SendData(STOP);
		delay(10000);						//Delay 10second

		TrafficLights(GREEN);
		SendData(GEAR2);
	}
	else
		printf("More Pedestrian\n");

}

//-----------------------------------------------

void TrafficLights(char mode){
	switch(mode){
		case RED:
			digitalWrite(TL_L1, HIGH);
			digitalWrite(TL_L2, LOW);
			
			digitalWrite(TL_R1, HIGH);
			digitalWrite(TL_R2, LOW);

			digitalWrite(PTL_L_F, LOW);
			digitalWrite(PTL_L_B, LOW);
			digitalWrite(PTL_R_F, LOW);
			digitalWrite(PTL_R_B, LOW);

			printf("RED ON\n");
			break;
		case ORANGE:
			digitalWrite(TL_L1, LOW);
			digitalWrite(TL_L2, LOW);
			
			digitalWrite(TL_R1, LOW);
			digitalWrite(TL_R2, LOW);

			digitalWrite(PTL_L_F, LOW);
			digitalWrite(PTL_L_B, LOW);
			digitalWrite(PTL_R_F, LOW);
			digitalWrite(PTL_R_B, LOW);
			printf("ORANGE ON\n");
			break;
		case GREEN:
			digitalWrite(TL_L1, LOW);
			digitalWrite(TL_L2, HIGH);
			
			digitalWrite(TL_R1, LOW);
			digitalWrite(TL_R2, HIGH);

			digitalWrite(PTL_L_F, HIGH);
			digitalWrite(PTL_L_B, HIGH);
			digitalWrite(PTL_R_F, HIGH);
			digitalWrite(PTL_R_B, HIGH);
			printf("GREEN ON\n");
			break;
		default:
			printf("WTF? TrafficLights Default\n");
			break;
	}
}

//-----------------------------------------------

int SendData(char command){
	switch(command){
		case GEAR1:
			digitalWrite(DATA1, HIGH);
			digitalWrite(DATA2, LOW);
			break;
		case GEAR2:
			digitalWrite(DATA1, LOW);
			digitalWrite(DATA2, HIGH);
			break;
		case TEST:
			digitalWrite(DATA1, HIGH);
			digitalWrite(DATA2, HIGH);
			break;
		case STOP:
			digitalWrite(DATA1, LOW);
			digitalWrite(DATA2, LOW);
			break;
		default:
			printf("OMG! SendData Default\n");
			return 1;
	}
	return 0;	//Return Value for printf()
}
