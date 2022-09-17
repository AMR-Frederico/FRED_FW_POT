#include <Arduino.h>
#include <Main/config.h>

class motor
{
private:
  
public:
    int In_A ;
    int In_B ; 
    int Pwm  ;
    int CANAL ; 
    motor(int In_A, int In_B,int Pwm);
    void begin();

};

motor::motor(int IN_A, int IN_B,int PWM)
{   
    In_A = IN_A ;
    In_B = IN_B ;
    Pwm = PWM ; 
    
};

void motor::begin()
{
    pinMode(In_A,OUTPUT);
    pinMode(In_B,OUTPUT);
    ledcAttachPin(Pwm, CANAL);
    ledcSetup(CANAL, FREQUENCIA, 10);
    digitalWrite(In_A, LOW);
    digitalWrite(In_B, LOW);
}

