#define SENTRAL	      1
#define LEFT	        0
#define RIGHT	        2
#define MAX_SENSORS   2

#define WHITE	600
#define GRAY	  400
#define BLACK	200

#define READ_SENTRAL	A3
#define READ_LEFT		  A0
#define READ_RIGHT		A4

#define MAX_ERR 		2048

float sensorsFeedBack(int* sensors);
void  sensorsRead(int* sensors);
bool  isAllSensorsWhite(int* sensors);
bool  isAllSensorsBlack(int* sensors);
