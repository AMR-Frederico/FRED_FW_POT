#include <Arduino.h>


#define LOOP_TIME 200000  

#define CANAL_M1 0
#define CANAL_M2 1
#define CANAL_M3 2
#define CANAL_M4 3

#define PWM_MIM 450
#define PWM_MAX 1023
#define SATURATION 1020

#define  FREQUENCIA 1000  


#define L  300

//define the pins from the HARDWARE project 

//H Bridge 
#define  M1_IN2  21
#define  M1_PWM  32
#define  M1_IN1  22 

#define  M2_IN1  19
#define  M2_IN2  23
#define  M2_PWM  25

#define  M3_IN1  4
#define  M3_IN2  5
#define  M3_PWM  27

#define  M4_IN1  18
#define  M4_IN2  15
#define  M4_PWM  12

//encoder

//debug led
#define  LED_BUILD_IN  2
#define  LED_STRIP  14
//serial infor
#define  SERIAL_RATE  115200
//kinematics configs 

// //radius of the wheel in milimiters 
#define RADIUS 75

// //distance between wheel contact point 
#define DISTANCE 300
// //Encoder info 

// const float TICKS = 15;

// 1600 rpm -> 1023 pwm 
// 0 -> 0 pwn 

// 0 a 1023 = 1024 partes

// 1,56 rpm = 0 pwm 

// v = (2*pi*f*rpm)*R
// v = (2*pi*100*1,56*pwm)/0,075
// v = 73 pwm 

// pwm = v/73

// VR = 0,18*(v - 0,0017w*)
// VL = 0,18*(v + 0,0017w*) 

#define MAX_RPM 1023
#define MAX_SPEED 10 //m/s 