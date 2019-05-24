#include <EEPROM.h>
#include <FastPID.h>

#include "Motors.h"
#include "Sensors.h"

#define STATE_LINE        0 //движение по линии
#define STATE_DASH        1 //движение по пунктиру
#define STATE_STEPS       2 //движение по ступенткам
#define STATE_CROSSROAD   3 //движение по перекрёстку
#define STATE_FINDING     4 //поиск ступенек

#define START 14

//float Kp=3.1, Ki=0.0, Kd=0.0, Hz=1000;// <-- РАБОЧЕЕ!  // скор - 200, разр крона 7.3 в
//float Kp=3.1, Ki=3.9, Kd=2.6, Hz=1000; //<-- РАБОЧЕЕ!  // скор - 200, разр крона 7.3 в
//float Kp=3.0, Ki=4.3, Kd=2.6, Hz=1000; // <-- РАБОЧЕЕ!  // скор - 210, разр крона 7.3 в ***** проходит ступени, не проходит крутой поворот в пуктир
//float Kp=2.9, Ki=4.0, Kd=2.0, Hz=1000;// <-- РАБОЧЕЕ!  // скор - 210, разр крона 7.3 в ***** проходит всё
//float Kp=2.9, Ki=4.0, Kd=2.0, Hz=1000;// <-- РАБОЧЕЕ!  // скор - 255, разр крона < 7.3 в ***** проходит всё, экранирование на: Л св, СЛ фототранзистор, С св, Р развендены в стороны
float Kp = 2.2, Ki = 3.8, Kd=2.0, Hz=1000; // ?????  
int output_bits = 16;
bool output_signed = true;
FastPID myPID(Kp, Ki, Kd, Hz, output_bits, output_signed);

byte state = STATE_LINE;

byte sensors[MAX_SENSORS];
byte sensorsL[MAX_SENSORS];
byte sensorsM[MAX_SENSORS];
byte sensorsH[MAX_SENSORS];
int counter = 0;
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
    delay(1000);
    if(digitalRead(START) == LOW)
    {
      readNormal(normalL,normalSL,normalS,normalSR,normalR);
      while(digitalRead(START) == LOW)
      {
          delay(15);
      }
    }
    else
    {
        sensorsRead(sensors);
        for(i = 0; i < MAX_SENSORS;i++)
        {
            sensorsL[i] = sensors[i];
            Serial.println(sensors[i]);
        }
    
        //Serial.println("Step 1 Finish");
    
    
        /*
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
    
        Serial.println("Step 2 Finish");*/
    
    
        
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
    
        
        /*
        Serial.print(sensorsL[0]); 
        Serial.print("  ");
        Serial.print(sensorsM[0]);
        Serial.print("  ");
        Serial.print(sensorsH[0]);
        Serial.print("  ");//*/
        generateNormal(normalL, LEFT, sensorsL[LEFT],sensorsM[LEFT],sensorsH[LEFT]);
        generateNormal(normalSL, S_LEFT, sensorsL[S_LEFT],sensorsM[S_LEFT],sensorsH[S_LEFT]);
        generateNormal(normalS, SENTRAL, sensorsL[SENTRAL],sensorsM[SENTRAL],sensorsH[SENTRAL]);
        generateNormal(normalSR, S_RIGHT, sensorsL[S_RIGHT],sensorsM[S_RIGHT],sensorsH[S_RIGHT]);
        generateNormal(normalR, RIGHT, sensorsL[RIGHT],sensorsM[RIGHT],sensorsH[RIGHT]);
        //Serial.println("Step 3 Finish");
        writeNormal(normalL,normalSL,normalS,normalSR,normalR);
        while(digitalRead(START) == HIGH)
        {
        }
        
    }
    
    delay(2000);
    
    
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
    sensorsRead(sensors);
   // sensorsRead2(sensors, normalL, normalSL, normalS, normalSR, normalR);
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
        return STATE_CROSSROAD;
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
        return STATE_LINE;
    }
    setMotorPWMPID(NORMAL_SPEED,(myPID.step(MAX_ERR, MAX_ERR))); 
    return STATE_CROSSROAD;
}

void readNormal(byte *normalL,byte *normalSL,byte *normalS,byte *normalSR,byte *normalR)
{
    int i;
    for(i = 0; i < MAX_VAL; i++)
    {
        normalL[i] = EEPROM.read(i);
    }
    for(i = 0; i < MAX_VAL; i++)
    {
        normalSL[i] = EEPROM.read(i + MAX_VAL);
    }
     for(i = 0; i < MAX_VAL; i++)
    {
        normalS[i] = EEPROM.read(i + 2*MAX_VAL);
    }
    for(i = 0; i < MAX_VAL; i++)
    {
        normalSR[i] = EEPROM.read(i + 3*MAX_VAL);
    }
    for(i = 0; i < MAX_VAL; i++)
    {
        normalR[i] = EEPROM.read(i + 4*MAX_VAL);
    }
}

void writeNormal(byte *normalL,byte *normalSL,byte *normalS,byte *normalSR,byte *normalR)
{
    int i;
    for(i = 0; i < MAX_VAL; i++)
    {
        EEPROM.write(i,normalL[i]);
    }
    for(i = 0; i < MAX_VAL; i++)
    {
        EEPROM.write(i + 1*MAX_VAL,normalSL[i]);
    }

    for(i = 0; i < MAX_VAL; i++)
    {
        EEPROM.write(i + 2*MAX_VAL,normalS[i]);
    }
    for(i = 0; i < MAX_VAL; i++)
    {
        EEPROM.write(i + 3*MAX_VAL,normalSR[i + 3*MAX_VAL]);
    }
    for(i = 0; i < MAX_VAL; i++)
    {
        EEPROM.write(i + 4*MAX_VAL,normalR[i + 4*MAX_VAL]);
    }
}








   
