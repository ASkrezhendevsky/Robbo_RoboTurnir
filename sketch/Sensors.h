#define LEFT          0
#define S_LEFT	      1

#define SENTRAL        2

#define S_RIGHT	      3
#define RIGHT         4

#define MAX_SENSORS   5

#define MAX_VAL   64
/*
#define MAX_WHITE     180
#define WHITE	        160
#define BRIGHT_GRAY   130
#define GRAY	        100
#define DARK_GRAY     55
#define BLACK	        50*/

#define MAX_SENS_VAL  64
#define MAX_WHITE     64
#define WHITE         10
#define BRIGHT_GRAY   20
#define GRAY          30
#define DARK_GRAY     40
#define BLACK         50

#define READ_SENTRAL	1
#define READ_LEFT		  5
#define READ_RIGHT		2

#define MAX_ERR 		1023

int sensorsFeedBack(byte* sensors);
void  sensorsRead(byte* sensors);
bool  isAllSensorsWhite(byte* sensors);
bool  isAllSensorsBlack(byte* sensors);

void generateNormal( byte *normal,int sensor, byte low,byte med,byte high);
void sensorsRead2(byte* sensors,byte* normalL,byte* normalSL,byte* normalS,byte* normalSR,byte* normalR);
byte getNormal(byte *normal,int val);
