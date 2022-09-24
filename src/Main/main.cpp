
#include <Main/config.h>
#include <Main/ros_com.h>


#include <Main/controler.h>


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

}
