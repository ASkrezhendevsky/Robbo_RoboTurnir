#include <Arduino.h>
#include "Sensors.h"

int sensorsFeedBack(int* sensors)
{
	if(sensors[SENTRAL] <= BLACK)
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
		if(sensors[RIGHT] > sensors[LEFT])
		{
			return sensors[RIGHT];
		}
		else
		{
			return -sensors[LEFT];
		}
	}
}

void sensorsRead(int* sensors)
{
	sensors[RIGHT] = (analogRead(READ_RIGHT)>>1);       // >>1 деление на два
	sensors[LEFT] = (analogRead(READ_LEFT)>>1);         
	sensors[SENTRAL] = (analogRead(READ_SENTRAL)>>1);   
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
	if(sensors[SENTRAL] >= GRAY)
	{
		return false;
	}
	if(sensors[RIGHT] >= GRAY)
	{
		return false;
	}
	if(sensors[LEFT] >= GRAY)
	{
		return false;
	}
	return true;
}
