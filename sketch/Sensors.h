#define SENTRAL	      2
#define S_LEFT	      1
#define S_RIGHT	      3
#define LEFT          0
#define RIGHT         4
#define MAX_SENSORS   5
/*
#define MAX_WHITE     180
#define WHITE	        160
#define BRIGHT_GRAY   130
#define GRAY	        100
#define DARK_GRAY     55
#define BLACK	        50*/

#define MAX_SENS_VAL  180
#define MAX_WHITE     180
#define WHITE         50
#define BRIGHT_GRAY   57
#define GRAY          100
#define DARK_GRAY     170
#define BLACK         190

#define READ_SENTRAL	1
#define READ_LEFT		  5
#define READ_RIGHT		2

#define MAX_ERR 		1023

int sensorsFeedBack(int* sensors);
void  sensorsRead(int* sensors);
bool  isAllSensorsWhite(int* sensors);
bool  isAllSensorsBlack(int* sensors);
