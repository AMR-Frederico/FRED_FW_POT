
#include <Main/config.h>
#include <Main/ros_com.h>
#include <Main/controler.h>
#include <Main/led_strip.h>


#include "encoderR.h"
EncoderR encoderRight;
#include "encoderL.h"
EncoderL encoderLeft;

#include "controler.h"
Controler esquerda_controler(5,1,1);
Controler direita_controler(5,1,1);

const int ACC = 50 ;
const int GAIN = 1 ;
const int GAIN_ANGULAR = 7;

bool _connect = false ;

float rpm_right = 0 ;
float rpm_left = 0;

int rpm = 0;
int rpm_controled = 0;

bool debug = false;



void setup() { 
  ros_init();
  led_strip_init();
  encoderLeft.setup();
  encoderRight.setup();
  pinMode(LED_BUILD_IN,OUTPUT);
  digitalWrite(LED_BUILD_IN,HIGH);
  
}

void loop() 
{   
    //add conection protection 
     if(!rosConnected(nh,_connect))
       write2motors( 0,0);

    

    float linear = getLinear();//robot
    float angular = getAngular();//robot


    //---------------------LEFT-------------------------------------------
    
    //status -------encoder 
    double angle_encoder_read_left  = encoderLeft.readAngle();

    double rpm_encoder_read_left = encoderLeft.readRPM();

    double ticks_encoder_read_left = encoderLeft.readTicks();

    //cmd------ 

    float angular_speed_left = cinematic_left(linear,angular,GAIN); //wheel [rad/s]

    rpm_left = angular2rpm(angular_speed_left);// [RPM]

    // float controled_speed_left = control.pid(input,kp,ki,kp) ; #output same unity [RPM]

    // float controled_RPM_left = rpm_left;
    float controled_RPM_left = esquerda_controler.output(rpm_left,rpm_encoder_read_left);

    //------------------------------RIGHT-------------------------------------------

    //status -- encoder 

    double angle_encoder_read_right = encoderRight.readAngle();

    double rpm_encoder_read_right = encoderRight.readRPM();

    double ticks_encoder_read_right = encoderRight.readTicks();

    //cmd -- 

    float angular_speed_right = cinematic_right(linear,angular,GAIN); //wheel [RAD/S]

    float rpm_right = angular2rpm(angular_speed_right);   // [RPM]

    // float controled_RPM_right = rpm_right;
    float controled_RPM_right = direita_controler.output(rpm_right,rpm_encoder_read_right);

  //----------------debug------------------------------
    if(debug){
    rpm = getRPMsetpoint();
    rpm_controled =direita_controler.output(rpm,rpm_encoder_read_left);
    write2motor(rpm,4);
    write2motor(rpm_controled,4);
    }
  //--------------------------execute-----------------

    if(!debug){
    write2motors(controled_RPM_left,controled_RPM_right);
    }


    ros_loop(angular_speed_right,angular_speed_left,angle_encoder_read_left,angle_encoder_read_right,rpm_encoder_read_left ,rpm_encoder_read_right,ticks_encoder_read_left,ticks_encoder_read_right,rpm_controled);
    nh.spinOnce();
}