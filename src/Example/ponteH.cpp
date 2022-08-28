#include "Arduino.h"

#define S1_M1 21
#define S2_M1 22
#define PWM_M1 32

#define S1_M2 19
#define S2_M2 23
#define PWM_M2 25 

#define S1_M3 5
#define S2_M3 4
#define PWM_M3 27

#define S1_M4 18
#define S2_M4 15
#define PWM_M4 12

const int freq = 5000;

const int ledChannel1 = 0;
const int ledChannel2 = 1;
const int ledChannel3 = 2;
const int ledChannel4 = 3;

const int resolution = 8;

void setup()
{
  pinMode(S1_M1, OUTPUT); 
  pinMode(S2_M1, OUTPUT); 
  
  pinMode(S1_M2, OUTPUT); 
  pinMode(S2_M2, OUTPUT); 

  pinMode(S1_M3, OUTPUT); 
  pinMode(S2_M3, OUTPUT); 

  pinMode(S1_M4, OUTPUT); 
  pinMode(S2_M4, OUTPUT); 

  pinMode(PWM_M1, OUTPUT); 
  pinMode(PWM_M2, OUTPUT); 
  pinMode(PWM_M3, OUTPUT); 
  pinMode(PWM_M4, OUTPUT); 

  ledcSetup(ledChannel1, freq, resolution);
  ledcSetup(ledChannel2, freq, resolution);
  ledcSetup(ledChannel3, freq, resolution);
  ledcSetup(ledChannel4, freq, resolution);

  ledcAttachPin(PWM_M1, ledChannel1);
  ledcAttachPin(PWM_M2, ledChannel2);
  ledcAttachPin(PWM_M3, ledChannel3);
  ledcAttachPin(PWM_M4, ledChannel4);

  ledcWrite(ledChannel1, 100);
  ledcWrite(ledChannel2, 100);
  ledcWrite(ledChannel3, 100);
  ledcWrite(ledChannel4, 100);

  digitalWrite(S1_M1, 1); 
  digitalWrite(S1_M2, 1); 
  digitalWrite(S1_M3, 1); 
  digitalWrite(S1_M4, 1); 

  digitalWrite(S2_M1, 0);
  digitalWrite(S2_M2, 0);
  digitalWrite(S2_M3, 0);
  digitalWrite(S2_M4, 0);

}

void loop()
{

}