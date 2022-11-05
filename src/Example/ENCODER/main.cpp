#include <Arduino.h>

#include "encoder.h"
Encoder encoder ;

double curEncoderRPM ; 
double encoderRatio = 1;
double reducerRatio = 1;
double curAxisRPM; 
double curEncoderAngle; 
double curAxisAngle ;
double curMotorRPM ; 


void setup(){
    Serial.begin(115200);
    encoder.setup();

}

void loop(){

//Read and convert Current encoder Velocity
    curEncoderRPM = encoder.readRPM(); //Encoder Read
    curAxisRPM = curEncoderRPM / encoderRatio;
    curMotorRPM = curAxisRPM * reducerRatio;

    //Read and convert Current encoder Angle
    curEncoderAngle = encoder.readAngle(); //Encoder Read
    curAxisAngle = curEncoderAngle / encoderRatio;

    Serial.print(" ");
    Serial.print("|");
    Serial.print("CURENcoderRPM : ");
    Serial.print(curEncoderRPM);
    Serial.print("|");
    Serial.print(" curAxisRPM: ");
    Serial.print(curAxisRPM);
    Serial.print("|");
    Serial.print(" curEncoderAngle: ");
    Serial.print(curEncoderAngle);
    Serial.print("|");
    Serial.print(" curAxisAngle: ");
    Serial.print(curAxisAngle);
    Serial.println("");

   

}