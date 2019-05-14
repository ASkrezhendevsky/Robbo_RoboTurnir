#include <Arduino.h>
#include "Sensors.h"

int sensorsFeedBack(int* sensors)
{
	if(sensors[SENTRAL] <= GRAY && sensors[LEFT] > DARK_GRAY && sensors[RIGHT] > DARK_GRAY)
	{    
      return -sensors[RIGHT]+sensors[LEFT];
	}
	else
	{
      if(sensors[RIGHT] < sensors[LEFT])
      {
          return MAX_WHITE +  MAX_WHITE +sensors[RIGHT] - sensors[LEFT];
      }
      else
      {
          return -MAX_WHITE- MAX_WHITE+ sensors[RIGHT] - sensors[LEFT];
      }
	}
}

void sensorsRead(int* sensors)
{
  	sensors[RIGHT] = (analogRead(2)>>1);       
  	sensors[LEFT] = (analogRead(5)>>1);         
  	sensors[SENTRAL] = (analogRead(1)>>1);   
}

bool isAllSensorsWhite(int* sensors)
{
	if(sensors[SENTRAL] <= WHITE)
	{
		return false;
	}
	if(sensors[RIGHT] <= WHITE)
	{
		return false;
	}
	if(sensors[LEFT] <= WHITE)
	{
		return false;
	}
	return true;
	
}

bool isAllSensorsBlack(int* sensors)
{
	if(sensors[SENTRAL] >= BLACK)
	{
		return false;
	}
	if(sensors[RIGHT] >= BLACK)
	{
		return false;
	}
	if(sensors[LEFT] >= BLACK)
	{
		return false;
	}
	return true;
}
