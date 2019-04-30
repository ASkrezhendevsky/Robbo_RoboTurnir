

#include <FastPID.h>

#include "Motors.h"

float Kp=0.1, Ki=0.5, Kd=0, Hz=10;
int output_bits = 8;
bool output_signed = false;

FastPID myPID(Kp, Ki, Kd, Hz, output_bits, output_signed);

void setup()
{
  
}

void loop()
{
  int setpoint = 512; 
  int feedback = 512;
  uint8_t output = myPID.step(setpoint, feedback);
}
   
