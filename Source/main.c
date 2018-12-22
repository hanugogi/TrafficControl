#include<stdio.h>
#include<errno.h>
#include<wiringPi.h>

//-----------------------------------------------

#define TL_L1	//Traffic Light Left
#define TL_L2
#define TL_R1	//Traffic Light Right
#define TL_R2

#define PTL_L_F	//Pedestrian Traffic Light Left Front
#define PTL_L_B	//Pedestrian Traffic LIght Left Backward
#define PTL_R_F	//Pedestrian Traffic Light Right Front
#define PTL_R_B	//Pedestrian Traffic Light Right Backward

#define IR_L1	//Left IRsensor For Car First
#define IR_L2	//Left IRsensor For Car Second
#define IR_R1	//Right IRsensor For Car First
#define IR_R2	//Right IRsensor For Car Second

#define PIR_L	//Left IRSensor For Pedestrian
#define PIR_R	//Right IRSensor For Pedestrian

//-----------------------------------------------

int main(){
	if(wiringPiSetup() == -1){
		perror("wiringPi");
		return 1;
	}
			
}
