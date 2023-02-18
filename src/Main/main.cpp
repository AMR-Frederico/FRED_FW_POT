
#include <Main/config.h>
#include <Main/ros_com.h>
#include <Main/controler.h>

#include "MedianFilter.h"

#include "encoder.h"

Encoder encoder(34, 35, 39,36);

MedianFilter encoderRightFilter(33,0);
MedianFilter encoderLeftFilter(33,0);


#include "controler.h"
Controler  esquerda_controler(0.4,0.01,0.08);  //(p,i,d)
// Controler  direita_controler(0.4,0.01,0.008);
Controler  direita_controler(0.4 , 0.0, 0.01 );  //(p,i,d)



const int ACC = 50 ;
const int GAIN = 1 ;
const int GAIN_ANGULAR = 7;

bool _connect = false ;

float rpm_right = 0 ;
float rpm_left = 0;

int rpm = 0;
int rpm_controled = 0;

bool debug = true;




void setup() { 
  ros_init();
  encoder.setup();
}

void loop() 
{   
    //add conection protection 
     if(!rosConnected(nh,_connect))
       write2motors( 0,0);

    

    float linear = getLinear();//robot
    float angular = getAngular();//robot


    //---------------------LEFT-------------------------------------------
    
    // status -------encoder 
    double angle_encoder_read_left  = encoder.readAngle(LEFT);

    double rpm_encoder_read_left = encoder.readRPM(LEFT);
    encoderLeftFilter.in(rpm_encoder_read_left);

    rpm_encoder_read_left = encoderLeftFilter.out();

    double ticks_encoder_read_left = encoder.readPulses(LEFT);

    // cmd------ 

    float angular_speed_left = cinematic_left(linear,angular,GAIN); //wheel [rad/s]

    rpm_left = angular2rpm(angular_speed_left);// [RPM]
    // rpm_left =  saturation(rpm_left,800);

    // float controled_RPM_left = rpm_left;
    float controled_RPM_left = esquerda_controler.output(rpm_left,rpm_encoder_read_left);

    //------------------------------RIGHT-------------------------------------------

    //status -- encoder 

    double angle_encoder_read_right = encoder.readAngle(RIGHT);

    double rpm_encoder_read_right = encoder.readRPM(RIGHT);
    encoderRightFilter.in(rpm_encoder_read_right);
    rpm_encoder_read_right = encoderRightFilter.out();

    double ticks_encoder_read_right = encoder.readPulses(RIGHT);

    //cmd -- 

    float angular_speed_right = cinematic_right(linear,angular,GAIN); //wheel [RAD/S]

    rpm_right = angular2rpm(angular_speed_right);   // [RPM]
    // rpm_right = saturation(rpm_right,800);
    // float controled_RPM_right = rpm_right;
    float controled_RPM_right = direita_controler.output(rpm_right,rpm_encoder_read_right);

  //----------------debug------------------------------
    if(debug){
    rpm = getRPMsetpoint();
    rpm_controled = direita_controler.output(rpm,rpm_encoder_read_right);
    write2motor(rpm_controled,2);
    //write2motor(rpm,2);
    }
  //--------------------------execute-----------------

    if(!debug){
    write2motors(controled_RPM_left,controled_RPM_right);
    }


    ros_loop(angular_speed_right,        angular_speed_left,
             angle_encoder_read_left,    angle_encoder_read_right,
             rpm_encoder_read_left ,     rpm_encoder_read_right,
             direita_controler.error,    direita_controler.integral,
             rpm_controled,              
             controled_RPM_left,         rpm_left);
    nh.spinOnce();
}