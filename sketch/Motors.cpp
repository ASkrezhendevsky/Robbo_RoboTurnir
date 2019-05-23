#include <Arduino.h>
#include "Motors.h"

void setMotorDirForward()
{
    setMotorDir(FORWARD,FORWARD);
}

void setMotorDirBackward()
{
    setMotorDir(BACKWARD,BACKWARD);
}

void setMotorDir(int lDir,int rDir)
{
    digitalWrite(MOTOR_LEFT_DIR,lDir);
    digitalWrite(MOTOR_RIGHT_DIR,rDir);
}

void setMotorPWM(int lPower,int rPower)
{
    analogWrite(MOTOR_LEFT_POW,lPower);
    analogWrite(MOTOR_RIGHT_POW,rPower);
}

void setMotorBreakL()
{
    digitalWrite(MOTOR_LEFT_DIR,HIGH);
    digitalWrite(MOTOR_LEFT_POW,HIGH);
}

void setMotorBreakR()
{
    digitalWrite(MOTOR_RIGHT_DIR,HIGH);
    digitalWrite(MOTOR_RIGHT_POW,HIGH);
}

void setMotorPWMPID(int Power,int PID)
{
    int left = Power-PID;
    int right = Power+PID;

    if(left <= 0)
    {
        left = 0;
    }

    if(right <= 0)
    {        
        right = 0;
    } 
    
    if(left > 255)
    {
        left = 255;
    } 

    if(right > 255)
    {
        right = 255;
    }


    
    setMotorPWM(left, right);
}
