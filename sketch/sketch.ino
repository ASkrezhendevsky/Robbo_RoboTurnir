#include <FastPID.h>

#include "Motors.h"
#include "Sensors.h"

#define STATE_LINE        0 //движение по линии
#define STATE_DASH        1 //движение по пунктиру
#define STATE_STEPS       2 //движение по ступенткам
#define STATE_CROSSROAD   3 //движение по перекрёстку
#define STATE_FINDING     4 //поиск ступенек

#define START 14

//float Kp=0.42, Ki=3.92, Kd=12.9, Hz=100000;
float Kp=2.22, Ki=1.8, Kd=1.8, Hz=1000;

//float Kp=1.92, Ki=0.0, Kd=0.0, Hz=1000;
int output_bits = 16;
bool output_signed = true;
FastPID myPID(Kp, Ki, Kd, Hz, output_bits, output_signed);

byte state = STATE_LINE;

byte sensors[MAX_SENSORS];
byte sensorsL[MAX_SENSORS];
byte sensorsM[MAX_SENSORS];
byte sensorsH[MAX_SENSORS];
int counter =0;
int i;

byte normalL[MAX_VAL];
byte normalSL[MAX_VAL];
byte normalS[MAX_VAL];
byte normalSR[MAX_VAL];
byte normalR[MAX_VAL];

void setup()
{
    Kp = Kp*NORMAL_SPEED/190;
    Ki = Ki*NORMAL_SPEED/190;
    Kd = Kd*NORMAL_SPEED/190;
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
    delay(400);
    sensorsRead(sensors);
    for(i = 0; i < MAX_SENSORS;i++)
    {
        sensorsL[i] = sensors[i];
        Serial.println(sensors[i]);
    }

    Serial.println("Step 1 Finish");


    
    while(digitalRead(START) == HIGH)
    {
    }
    delay(400);
    sensorsRead(sensors);
    for(i = 0; i < MAX_SENSORS;i++)
    {
        sensorsM[i] = sensors[i];
        Serial.println(sensors[i]);
    }

    Serial.println("Step 2 Finish");


    
    while(digitalRead(START) == HIGH)
    {
    }
    delay(400);
    sensorsRead(sensors);
    for(i = 0; i < MAX_SENSORS;i++)
    {
        sensorsH[i] = sensors[i];
        Serial.println(sensors[i]);
    }

    
    Serial.print(sensorsL[0]); 
    Serial.print("  ");
    Serial.print(sensorsM[0]);
    Serial.print("  ");
    Serial.print(sensorsH[0]);
    Serial.print("  ");
    generateNormal(normalL, LEFT, sensorsL[LEFT],sensorsM[LEFT],sensorsH[LEFT]);
    for(i = 0; i < MAX_VAL;i++)
    {
        Serial.println(normalL[i]);
    }
    generateNormal(normalSL, S_LEFT, sensorsL[S_LEFT],sensorsM[S_LEFT],sensorsH[S_LEFT]);
    generateNormal(normalS, SENTRAL, sensorsL[SENTRAL],sensorsM[SENTRAL],sensorsH[SENTRAL]);
    generateNormal(normalSR, S_RIGHT, sensorsL[S_RIGHT],sensorsM[S_RIGHT],sensorsH[S_RIGHT]);
    generateNormal(normalR, RIGHT, sensorsL[RIGHT],sensorsM[RIGHT],sensorsH[RIGHT]);

    Serial.println("Step 3 Finish");
    
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
    Serial.println(sensors[2]);//*/
    
    /*
    //sensorsRead2(sensors);
    sensorsRead2(sensors, normalL, normalSL, normalS, normalSR, normalR);
    int feedback = sensorsFeedBack(sensors);
    Serial.print(" sensorsFeedBack = ");
    Serial.print(feedback);
    Serial.print(" L = ");
    Serial.print(sensors[0]);
    Serial.print(" SL = ");
    Serial.print(sensors[1]);
    Serial.print(" s = ");
    Serial.print(sensors[2]);
    Serial.print(" SR = ");
    Serial.print(sensors[3]);
    Serial.print(" R = ");
    Serial.print(sensors[4]);
    Serial.print(" myPID = ");
    Serial.println(myPID.step(MAX_ERR, feedback+MAX_ERR));
    //delay(100);//*/

/*
    counter++;
    if(counter > 1000)
    {
        setMotorBreakL();
        setMotorBreakR();
        while(true)
        {
        }
    }*/

    
    //*
    sensorsRead2(sensors, normalL, normalSL, normalS, normalSR, normalR);

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
    setMotorPWMPID(NORMAL_SPEED,(myPID.step(MAX_ERR, MAX_ERR))); 
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








   
