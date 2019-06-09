
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

void setMotorPWMPID(int Power,int pid)
{
    int left = Power - pid;
    int right = Power + pid;
    
    if(left <= 0)
    {
        setMotorBreakL();
    }
    else
    {
        digitalWrite(MOTOR_LEFT_DIR,FORWARD);
        if(left > 255)
        {
            left = 255;
        } 
        analogWrite(MOTOR_LEFT_POW,left);
    }

    if(right <= 0)
    {        
        setMotorBreakR();
    } 
    else
    {
        digitalWrite(MOTOR_RIGHT_DIR,FORWARD);
        if(right > 255)
        {
            right = 255;
        }
        analogWrite(MOTOR_RIGHT_POW,right);
    }
}
