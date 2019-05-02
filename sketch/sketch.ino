#include <FastPID.h>

#include "Motors.h"
#include "Sensors.h"

#define STATE_LINE        0 //движение по линии
#define STATE_DASH        1 //движение по пунктиру
#define STATE_STEPS       2 //движение по ступенткам
#define STATE_CROSSROAD   3 //движение по перекрёстку
#define STATE_FINDING     4 //поиск ступенек

float Kp=0.46, Ki=0.36, Kd=1.3, Hz=1000;
int output_bits = 8;
bool output_signed = true;
FastPID myPID(Kp, Ki, Kd, Hz, output_bits, output_signed);

byte state = STATE_LINE;

int sensors[MAX_SENSORS];

void setup()
{
    pinMode(MOTOR_LEFT_DIR,OUTPUT);
    pinMode(MOTOR_RIGHT_DIR,OUTPUT);
    pinMode(MOTOR_LEFT_POW,OUTPUT);
    pinMode(MOTOR_RIGHT_POW,OUTPUT);

    Serial.begin(9600);
    setMotorDirForward();
    delay(1000);
    setMotorPWM(0,0);
}

void loop()
{
  /*
    int setpoint = 512; 
    int feedback = 512;
    uint8_t output = myPID.step(setpoint, feedback);
  */
   /* sensorsRead(sensors);
    Serial.print("sensorsFeedBack = ");
    Serial.println(sensorsFeedBack(sensors)+512);
    Serial.print("myPID = ");
    Serial.println(myPID.step(512, sensorsFeedBack(sensors)+512));
    delay(100);//*/
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
    }
    
}

byte moveAlongLine()
{
    if(isAllSensorsWhite(sensors))
    {
       // return STATE_DASH;
    }
    if(isAllSensorsBlack(sensors))
    {
       // return STATE_CROSSROAD;
    }
    setMotorPWMPID(NORMAL_SPEED,(myPID.step(512, sensorsFeedBack(sensors)+512)));  // >>1 деление на два
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








   
