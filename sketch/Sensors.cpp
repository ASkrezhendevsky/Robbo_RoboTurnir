#include <Arduino.h>
#include "Sensors.h"

int sensorsFeedBack(int* sensors)
{
  
  return -sensors[S_RIGHT]+sensors[LEFT];

  
	if(sensors[SENTRAL] >= GRAY && sensors[S_LEFT] < DARK_GRAY && sensors[S_RIGHT] < DARK_GRAY)
	{    
      return -sensors[S_RIGHT]+sensors[LEFT];
	}
	else
	{
      if(sensors[S_RIGHT] < sensors[S_LEFT])
      {
          return MAX_SENS_VAL +  MAX_SENS_VAL +sensors[S_RIGHT] - sensors[S_LEFT];
      }
      else
      {
          return -MAX_SENS_VAL- MAX_SENS_VAL+ sensors[S_RIGHT] - sensors[S_LEFT];
      }
	}
  
}

void sensorsRead(int* sensors)
{      
    sensors[S_LEFT] =   (analogRead(1)>>1);        
  	sensors[LEFT] =     (analogRead(2)>>1);         
  	sensors[SENTRAL] =  (analogRead(3)>>1);  
    sensors[S_RIGHT] =  (analogRead(4)>>1);  
    sensors[RIGHT] =    (analogRead(5)>>1);  
}

bool isAllSensorsWhite(int* sensors)
{
  byte i = 0; 
  for(i = 0;i < MAX_SENSORS;i++)
  {
      if(sensors[i] >= WHITE)
      {
          return false;
      }
  }
	return true;
	
}

bool isAllSensorsBlack(int* sensors)
{
	byte i = 0; 
  for(i = 0;i < MAX_SENSORS;i++)
  {
      if(sensors[i] <= BLACK)
      {
          return false;
      }
  }
  return true;
}
