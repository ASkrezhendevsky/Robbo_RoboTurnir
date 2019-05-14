#include <FastPID.h>

#include "Motors.h"
#include "Sensors.h"

#define STATE_LINE        0 //движение по линии
#define STATE_DASH        1 //движение по пунктиру
#define STATE_STEPS       2 //движение по ступенткам
#define STATE_CROSSROAD   3 //движение по перекрёстку
#define STATE_FINDING     4 //поиск ступенек

#define START 14

float Kp=0.92, Ki=0.72, Kd=2.6, Hz=1000;
//float Kp=1.92, Ki=0.0, Kd=0.0, Hz=1000;
int output_bits = 8;
bool output_signed = true;
FastPID myPID(Kp, Ki, Kd, Hz, output_bits, output_signed);

byte state = STATE_LINE;

int sensors[MAX_SENSORS];

void setup()
{
    Kp = Kp*NORMAL_SPEED/150;
    Ki = Ki*NORMAL_SPEED/150;
    Kd = Kd*NORMAL_SPEED/150;
    pinMode(MOTOR_LEFT_DIR,OUTPUT);
    pinMode(MOTOR_RIGHT_DIR,OUTPUT);
    pinMode(MOTOR_LEFT_POW,OUTPUT);
    pinMode(MOTOR_RIGHT_POW,OUTPUT);
    pinMode(START,INPUT);

    Serial.begin(9600);
    setMotorDirForward();
    setMotorPWM(0,0);
    while(digitalRead(START) == HIGH)
    {
    }
    delay(1000);
}

void loop()
{
  /*
    int setpoint = 512; 
    int feedback = 512;
    uint8_t output = myPID.step(setpoint, feedback);
  */
 /*
    sensorsRead(sensors);
    Serial.print(" sensorsFeedBack = ");
    Serial.print(sensorsFeedBack(sensors));
    Serial.print(" sensors[0] = ");
    Serial.print(sensors[0]);
    Serial.print(" sensors[1] = ");
    Serial.print(sensors[1]);
    Serial.print(" sensors[2] = ");
    Serial.println(sensors[2]);
    
    /*
    Serial.print("myPID = ");
    Serial.println(myPID.step(512, sensorsFeedBack(sensors)+512));
    delay(100);//*/



    
    //*
    sensorsRead(sensors);

    switch(state)
    {
        case STATE_LINE:
            state = moveAlongLine();
        break;
        case STATE_DASH:
            state = moveDottedLine();
        break;
        case STATE_CROSSROAD:
            state = moveCrossroad();
        break;
    }//*/
    
}

byte moveAlongLine()
{
    if(isAllSensorsWhite(sensors))
    {
        return STATE_DASH;
    }
    if(isAllSensorsBlack(sensors))
    {
       // return STATE_CROSSROAD;
    }
    setMotorPWMPID(NORMAL_SPEED,(myPID.step(MAX_ERR, sensorsFeedBack(sensors)+MAX_ERR))); 
    return STATE_LINE;
}

byte moveDottedLine()
{
    if(!isAllSensorsWhite(sensors))
    {
        return STATE_LINE;
    }
    setMotorPWM(NORMAL_SPEED,NORMAL_SPEED);
    return STATE_DASH;
}

byte moveCrossroad()
{
    if(!isAllSensorsBlack(sensors))
    {
        return STATE_CROSSROAD;
    }
    setMotorPWM(NORMAL_SPEED,NORMAL_SPEED);
    return STATE_CROSSROAD;
}








   
