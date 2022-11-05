
#include <Main/config.h>
#include <Main/ros_com.h>

#include <Main/controler.h>

#include <Main/led_strip.h>

const int ACC = 50 ;
const int GAIN = 1 ;
const int GAIN_ANGULAR = 7;

bool _connect = false ;


void setup() { 
  ros_init();
  led_strip_init();
  pinMode(LED_BUILD_IN,OUTPUT);
  digitalWrite(LED_BUILD_IN,HIGH);
  
}

void loop() 
{   

     if(!rosConnected(nh,_connect))
       write_all( 0,0);

    
    nh.spinOnce();

    float linear = getLinear();//robot
    float angular = getAngular();//robot

    angular = angular*GAIN_ANGULAR;
    
    float angular_speed_left = cinematic_left(linear,angular,GAIN); //wheel 
    float angular_speed_right = cinematic_right(linear,angular,GAIN); //wheel

    float controled_speed_left = angular_speed_left  ;
    // double controled_speed_left = rampa_profiler(speed_left,ACC) ;

    float controled_speed_right = angular_speed_right ;
    // double controled_speed_right = rampa_profiler(speed_right,ACC);
    
    write_all( controled_speed_left,controled_speed_right);

    ros_loop(angular_speed_right,angular_speed_left );
}



