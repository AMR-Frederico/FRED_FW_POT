
#include <Main/config.h>
#include <Main/ros_com.h>

#include <Main/controler.h>

#include <Main/led_strip.h>

const int ACC = 50 ;
const int GAIN = 1 ;

bool _connect = false ;


void setup() { 
  ros_init();
  led_strip_init();
  pinMode(LED_BUILD_IN,OUTPUT);
  digitalWrite(LED_BUILD_IN,HIGH);
  
}

void loop() 
{   

    // if(!rosConnected(nh,_connect))
    //     stop();

    ros_loop();
    
    nh.spinOnce();

    int linear = getLinear();
    int angular = getAngular();

    int speed_left = cinematic_left(linear,angular,GAIN);
    int speed_right = cinematic_right(linear,angular,GAIN);

    // int controled_speed_left = speed_left ;
    double controled_speed_left = rampa_profiler(speed_left,ACC) ;

     // int controled_speed_right = speed_right ;
    double controled_speed_right = rampa_profiler(speed_right,ACC);
    
    write_all( controled_speed_left,controled_speed_right);

}



