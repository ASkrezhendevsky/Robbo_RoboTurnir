#define SENTRAL	      1
#define LEFT	        0
#define RIGHT	        2
#define MAX_SENSORS   3

#define WHITE	  400
#define GRAY	  250
#define BLACK	  100

#define READ_SENTRAL	1
#define READ_LEFT		  5
#define READ_RIGHT		2

#define MAX_ERR 		1023

int sensorsFeedBack(int* sensors);
void  sensorsRead(int* sensors);
bool  isAllSensorsWhite(int* sensors);
bool  isAllSensorsBlack(int* sensors);
