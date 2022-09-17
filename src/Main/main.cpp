#include <ros.h>
#include <std_msgs/Int16.h>
#include <std_msgs/Float32.h>
#include <geometry_msgs/Twist.h>

#include <Arduino.h>

#include <Main/config.h>
#include <Main/ros_com.h>
#include <Main/power.h>



bool _connect = false ;

ros::NodeHandle  nh;

ros::Subscriber<std_msgs::Int16> subCmdWheels("cmd_wheels", cmdWheelsCB );
ros::Subscriber<std_msgs::Int16> subCmdRight("cmd_right_wheel",cmdRightWheelCB );
ros::Subscriber<geometry_msgs::Twist> subCmdVel("cmd_vel", cmdVelCB);

void setup() {
  //------------motors  
 
  
  pinMode(LED_BUILD_IN,OUTPUT);
  digitalWrite(LED_BUILD_IN,HIGH);
  
  nh.initNode();
  nh.subscribe(subCmdRight);
  nh.subscribe(subCmdWheels);
  nh.subscribe(subCmdVel);

}

void loop() 
{   
    if(!rosConnected(nh,_connect))
        stop();
  
    nh.spinOnce();

}
