
#include <EEPROM.h>
#include "FastPID.h"

#include "Motors.h"
#include "Sensors.h"

#define CUNTER_ON     false

#define STATE_LINE        0 //движение по линии
#define STATE_DASH        1 //движение по пунктиру
#define STATE_STEPS       2 //движение по ступенткам
#define STATE_CROSSROAD   3 //движение по перекрёстку
#define STATE_FINDING     4 //поиск ступенек
#define STATE_TEST     5 //

#define BTN_LONG          0  //
#define BTN_SHORT         1 //

#define START 14

//float Kp=3.1, Ki=0.0, Kd=0.0, Hz=1000;// <-- РАБОЧЕЕ!  // скор - 200, разр крона 7.3 в
//float Kp=3.1, Ki=3.9, Kd=2.6, Hz=1000; //<-- РАБОЧЕЕ!  // скор - 200, разр крона 7.3 в
//float Kp=3.0, Ki=4.3, Kd=2.6, Hz=1000; // <-- РАБОЧЕЕ!  // скор - 210, разр крона 7.3 в ***** проходит ступени, не проходит крутой поворот в пуктир
//float Kp=2.9, Ki=4.0, Kd=2.0, Hz=1000;// <-- РАБОЧЕЕ!  // скор - 210, разр крона 7.3 в ***** проходит всё
//float Kp=2.9, Ki=4.0, Kd=2.0, Hz=1000;// <-- РАБОЧЕЕ!  // скор - 255, разр крона < 7.3 в ***** проходит всё, экранирование на: Л св, СЛ фототранзистор, С св, Р развендены в стороны
//float Kp = 2.2, Ki = 3.8, Kd=2.0, Hz=1000; // ?????  
//float Kp=4.2, Ki=4.0, Kd=2.5, Hz=1000;// <-- РАБОЧЕЕ не очень!  // скор - 210 9v БП на новом аккуме слетает скор 180, 10 в
//float Kp=3.5, Ki=4.0, Kd=2.5, Hz=1000;//
//float Kp=2.6, Ki=0.0, Kd=0.0, Hz=1000;// <--   // скор - 180  акк 10v

//float Kp=2.9, Ki=4.0, Kd=2.0, Hz=1000;// <-- РАБОЧЕЕ!  // v = 190, U = 10.5 *** экранирование на: Л св, СЛ фототранзистор, С св, Р развендены в стороны

//float Kp=2.75, Ki=5.3, Kd=2.0, Hz=1000;// <-- РАБОЧЕЕ!  ***// v = 190, U = 10.5 *** экранирование на: Л св, СЛ фототранзистор, С св, Р развендены в стороны

//float Kp=2.85, Ki=3.9, Kd=100.7, Hz=1000;// <-- РАБОЧЕЕ!  *****// v = 190, U = 10.5 экранирование на: Л св, СЛ фототранзистор, С св, Р развендены в стороны

float Kp=2.89, Ki=3.9, Kd=100.7, Hz=1000;// <-- РАБОЧЕЕ!  // v = 220, U = 10.5 экранирование на: Л св, СЛ фототранзистор, С св, Р развендены в стороны

//float Kp=2.90, Ki=4.0, Kd=70.7, Hz=1000;// <-- РАБОЧЕЕ!  // v = 235, U = 10.5 экранирование на: Л св, СЛ фототранзистор, С св, Р развендены в стороны



int output_bits = 16;
bool output_signed = true;
FastPID myPID(Kp, Ki, Kd, Hz, output_bits, output_signed);

byte state = STATE_LINE;

byte sensors[MAX_SENSORS];
byte sensorsL[MAX_SENSORS];
byte sensorsM[MAX_SENSORS];
byte sensorsH[MAX_SENSORS];

byte normalL[MAX_VAL];
byte normalSL[MAX_VAL];
byte normalS[MAX_VAL];
byte normalSR[MAX_VAL];
byte normalR[MAX_VAL];

int counter = 0;
int i;
byte buttonStart = 0;

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
    
    delay(10);
    Serial.println("Ready");

    Serial.println("Read and start - LONG, other - SHORT");
    buttonStart = getButtonState(START);
    if(buttonStart == BTN_LONG)
    {
        readNormal(normalL,normalSL,normalS,normalSR,normalR);
    }
    else
    {
        Serial.println("Write new and test - LONG,read and test - SHORT");
        
        buttonStart = getButtonState(START);
        if(buttonStart == BTN_LONG)
        {
            Serial.println("Press Button for Write LOW");
            buttonStart = getButtonState(START);
            sensorsRead(sensors);
            for(i = 0; i < MAX_SENSORS;i++)
            {
                sensorsL[i] = sensors[i];
                Serial.println(sensors[i]);
            }
        
            Serial.println("Step 1 Finish");
            Serial.println("Press Button for Write HIGH");
        
            for(i = 0; i < MAX_SENSORS;i++)
            {
                buttonStart = getButtonState(START);
                sensorsRead(sensors);
                sensorsH[i] = sensors[i];
                Serial.println(sensorsH[i]);
            }
            generateNormal(normalL, LEFT, sensorsL[LEFT],sensorsM[LEFT],sensorsH[LEFT]);
            generateNormal(normalSL, S_LEFT, sensorsL[S_LEFT],sensorsM[S_LEFT],sensorsH[S_LEFT]);
            generateNormal(normalS, SENTRAL, sensorsL[SENTRAL],sensorsM[SENTRAL],sensorsH[SENTRAL]);
            generateNormal(normalSR, S_RIGHT, sensorsL[S_RIGHT],sensorsM[S_RIGHT],sensorsH[S_RIGHT]);
            generateNormal(normalR, RIGHT, sensorsL[RIGHT],sensorsM[RIGHT],sensorsH[RIGHT]);
            
            writeNormal(normalL,normalSL,normalS,normalSR,normalR);
            state = STATE_TEST;
            delay(20);
            
            Serial.println("Step 3 Finish");
            Serial.println("Press Button for start TEST");
            
            buttonStart = getButtonState(START);
        }
        else
        {
            readNormal(normalL,normalSL,normalS,normalSR,normalR);
            state = STATE_TEST;
        }
    }

    delay(10);
}

void loop()
{
    if(CUNTER_ON)
    {
        counter++;
        if(counter > 1000)
        {
            setMotorBreakL();
            setMotorBreakR();
            while(true)
            {}
        }
    }
    
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
        case STATE_TEST:
            //sensorsRead(sensors);
            sensorsRead2(sensors, normalL, normalSL, normalS, normalSR, normalR);
            int feedback = sensorsFeedBack(sensors);
            Serial.print(" sensorsFeedBack = ");
            Serial.print(feedback);
            Serial.print(" L = ");
            Serial.print(sensors[LEFT]);
            Serial.print(" SL = ");
            Serial.print(sensors[S_LEFT]);
            Serial.print(" s = ");
            Serial.print(sensors[SENTRAL]);
            Serial.print(" SR = ");
            Serial.print(sensors[S_RIGHT]);
            Serial.print(" R = ");
            Serial.print(sensors[RIGHT]);
            Serial.print(" myPID = ");
            Serial.println(myPID.step(MAX_ERR, feedback+MAX_ERR));
        break;
    }
}

byte moveAlongLine()
{
    int feedback = sensorsFeedBack(sensors);
    int pid = myPID.step(MAX_ERR, feedback+MAX_ERR);
    if(isAllSensorsWhite(sensors))
    {
        return STATE_DASH;
    }
    if(isAllSensorsBlack(sensors))
    {
        return STATE_CROSSROAD;
    }
    Serial.println(feedback);
    setMotorPWMPID(NORMAL_SPEED,pid); 
    return STATE_LINE;
}

byte moveDottedLine()
{
    if(!isAllSensorsWhite(sensors))
    {
        return STATE_LINE;
    }
    setMotorDirForward();
    setMotorPWMPID(NORMAL_SPEED,(myPID.step(MAX_ERR, MAX_ERR+80))); 
    //setMotorPWM(255,180); 
    return STATE_DASH;
}

byte moveCrossroad()
{
    if(!isAllSensorsBlack(sensors))
    {
        return STATE_LINE;
    }
    setMotorDirForward();
    setMotorPWM(255,180); 
    return STATE_CROSSROAD;
}

void readNormal(byte *normalL,byte *normalSL,byte *normalS,byte *normalSR,byte *normalR)
{
    int i;
    for(i = 0; i < MAX_VAL; i++)
    {
        normalL[i] = EEPROM.read(i);
        delay(5);
    }
    for(i = 0; i < MAX_VAL; i++)
    {
        normalSL[i] = EEPROM.read(i + MAX_VAL);
        delay(5);
    }
     for(i = 0; i < MAX_VAL; i++)
    {
        normalS[i] = EEPROM.read(i + 2*MAX_VAL);
        delay(5);
    }
    for(i = 0; i < MAX_VAL; i++)
    {
        normalSR[i] = EEPROM.read(i + 3*MAX_VAL);
        delay(5);
    }
    for(i = 0; i < MAX_VAL; i++)
    {
        normalR[i] = EEPROM.read(i + 4*MAX_VAL);
        delay(5);
    }
}

void writeNormal(byte *normalL,byte *normalSL,byte *normalS,byte *normalSR,byte *normalR)
{
    int i;
    for(i = 0; i < MAX_VAL; i++)
    {
        EEPROM.write(i,normalL[i]);
        delay(5);
    }
    for(i = 0; i < MAX_VAL; i++)
    {
        EEPROM.write(i + 1*MAX_VAL,normalSL[i]);
        delay(5);
    }

    for(i = 0; i < MAX_VAL; i++)
    {
        EEPROM.write(i + 2*MAX_VAL,normalS[i]);
        delay(5);
    }
    for(i = 0; i < MAX_VAL; i++)
    {
        EEPROM.write(i + 3*MAX_VAL,normalSR[i + 3*MAX_VAL]);
        delay(5);
    }
    for(i = 0; i < MAX_VAL; i++)
    {
        EEPROM.write(i + 4*MAX_VAL,normalR[i + 4*MAX_VAL]);
        delay(5);
    }
}

byte getButtonState(byte pin)
{
    while(digitalRead(pin) == HIGH)
    {
    }
    delay(1000);
    if(digitalRead(pin) == LOW)
    {
      while(digitalRead(pin) == LOW)
      {
          delay(15);
      }
      return BTN_LONG;
    }
    return BTN_SHORT;
}
