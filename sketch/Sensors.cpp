#include <Arduino.h>
#include "Sensors.h"

int sensorsFeedBack(byte* sensors)
{

  if(sensors[SENTRAL] >= 20 && sensors[LEFT] < 30 && sensors[RIGHT] < 30)
  {    
      Serial.print(1);
      return -sensors[S_RIGHT]+sensors[S_LEFT];
  }
  if(sensors[LEFT] < 30 && sensors[RIGHT] < 30)
  {
      if(sensors[S_RIGHT] < sensors[S_LEFT])
      {
        
          Serial.print(2);
          return MAX_SENS_VAL +  MAX_SENS_VAL +sensors[S_RIGHT] - sensors[S_LEFT];
        
      }
      else
      {
        
          Serial.print(3);
          return -MAX_SENS_VAL - MAX_SENS_VAL+ sensors[S_RIGHT] - sensors[S_LEFT];
        
      }
  }
  Serial.print(4);
  return -sensors[RIGHT] +   sensors[LEFT];
  
  
 /*
  if(sensors[SENTRAL] >= 170 && sensors[LEFT] < DARK_GRAY && sensors[RIGHT] < DARK_GRAY)
  {    
      return -sensors[S_RIGHT]+sensors[S_LEFT];
  }
 
  int lSum = (sensors[RIGHT] + sensors[S_RIGHT]);
  int rSum = (sensors[S_LEFT] + sensors[LEFT]);
  if(rSum > lSum)
  {
      return MAX_SENS_VAL + rSum - lSum;
  }
  else
  {
      return -MAX_SENS_VAL + rSum - lSum;
  }*/
  
  
  /*
  return -sensors[S_RIGHT]+sensors[LEFT];//*/

  /*
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
	}//*/
  
}

void sensorsRead(byte* sensors)
{      
    sensors[LEFT] =   (analogRead(1)>>4);        
  	sensors[S_LEFT] =     (analogRead(2)>>4);         
  	sensors[SENTRAL] =  (analogRead(3)>>4);  
    sensors[S_RIGHT] =  (analogRead(4)>>4);  
    sensors[RIGHT] =    (analogRead(5)>>4);  
}

void sensorsRead2(byte* sensors,byte* normalL,byte* normalSL,byte* normalS,byte* normalSR,byte* normalR)
{      
    sensors[LEFT] =       getNormal(normalL,(analogRead(1)>>4));        
    sensors[S_LEFT] =     getNormal(normalSL,(analogRead(2)>>4));         
    sensors[SENTRAL] =    getNormal(normalS,(analogRead(3)>>4));  
    sensors[S_RIGHT] =    getNormal(normalSR,(analogRead(4)>>4));  
    sensors[RIGHT] =      getNormal(normalR,(analogRead(5)>>4));  
}

byte getNormal(byte *normal,int val)
{
    return normal[val];
}

void generateNormal( byte *normal,int sensor, byte low,byte med,byte high)
{
    int i = 0;
    for(i = 0; i <= low; i++)
    {
        normal[i] = 0;
    }
    for(i = high; i < MAX_VAL; i++)
    {
        normal[i] = MAX_VAL;
    }
    
    for(i = low+1; i < high; i++)
    {
        //normal[i] = (byte)(((float)i-low) * MAX_VAL/2.0 / ((float)med - low));
        normal[i] = (byte)(((float)i-low) * MAX_VAL / ((float)high - low));
    }
    /*
    for(i = med; i < high; i++)
    {
        normal[i] = (byte)(MAX_VAL/2.0 + (float)((float)i-low) * MAX_VAL / ((float)high - med)/2.0);
    }*/
}

bool isAllSensorsWhite(byte* sensors)
{
  byte i; 
  for(i = 0;i < MAX_SENSORS;i++)
  {
      if(sensors[i] >= BRIGHT_GRAY)
      {
          return false;
      }
  }
	return true;
	
}

bool isAllSensorsBlack(byte* sensors)
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
