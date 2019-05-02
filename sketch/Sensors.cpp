#include <Arduino.h>
#include "Sensors.h"

int sensorsFeedBack(int* sensors)
{
	if(sensors[SENTRAL] >= GRAY)
	{
		if(sensors[RIGHT] > sensors[LEFT])
		{
			return MAX_ERR - sensors[RIGHT];
		}
		else
		{
			return - MAX_ERR + sensors[LEFT];
		}
	}
	else
	{
		//if(sensors[RIGHT] > sensors[LEFT])
		//{
			return -sensors[RIGHT]+sensors[LEFT];
		//}
		//else
		//{
		//	return sensors[LEFT]-sensors[RIGHT];
		//}
	}
}

void sensorsRead(int* sensors)
{
  	sensors[RIGHT] = (analogRead(2)>>1);       
  	sensors[LEFT] = (analogRead(5)>>1);         
  	sensors[SENTRAL] = 20;//(analogRead(READ_SENTRAL)>>1);   
}

bool isAllSensorsWhite(int* sensors)
{
	if(sensors[SENTRAL] <= GRAY)
	{
		return false;
	}
	if(sensors[RIGHT] <= GRAY)
	{
		return false;
	}
	if(sensors[LEFT] <= GRAY)
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
