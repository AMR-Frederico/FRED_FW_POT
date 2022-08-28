#include "Arduino.h"


//define the pins from the HARDWARE project 

//H Bridge 
const int M1_IN1 = 21; 
const int M1_IN2 = 22;
const int M1_PWM = 32;

const int M2_IN1 = 19;
const int M2_IN2 = 23;
const int M2_PWM = 25;

const int M3_IN1 = 5;
const int M3_IN2 = 4;
const int M3_PWM = 27 ;

const int M4_IN1 = 18;
const int M4_IN2 = 15;
const int M4_PWM = 12 ;

//encoder

//debug led
const int LED_BUILD_IN = 2;
const int LED_STRIP = 14;
//serial infor
const int SERIAL_RATE = 115200;
//kinematics configs 

// //radius of the wheel in milimiters 
const float RADIUS = 75;
// //distance between wheel contact point 
const float DISTANCE = 300;
// //Encoder info 

// const float TICKS = 15;