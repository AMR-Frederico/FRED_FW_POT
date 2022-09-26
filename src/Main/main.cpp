
#include <Main/config.h>
#include <Main/ros_com.h>


#include <Main/led_strip.h>


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
        stop();

    ros_loop();
    
    nh.spinOnce();

    int linear = getLinear();
    int angular = getAngular();

    int speed_left = cinematic_left(linear,angular,1);
    int speed_right = cinematic_right(linear,angular,1);

    int controled_speed_left = speed_left ;

    int controled_speed_right = speed_right ;
    
    write_all( controled_speed_left,controled_speed_right);

}
