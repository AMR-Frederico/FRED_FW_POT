#include <ros.h>
#include <std_msgs/Int16.h>
#include <std_msgs/Float32.h>
#include <geometry_msgs/Twist.h>

#include <Main/power.h>

ros::NodeHandle  nh;

ros::Subscriber<std_msgs::Int16> subCmdWheels("cmd_wheels", cmdWheelsCB );
ros::Subscriber<std_msgs::Int16> subCmdRight("cmd_right_wheel",cmdRightWheelCB );
ros::Subscriber<geometry_msgs::Twist> subCmdVel("cmd_vel", cmdVelCB);

bool rosConnected(ros::NodeHandle  nh,bool _connect){
    bool connected = nh.connected();
    if(_connect != connected){
        _connect = connected;
        digitalWrite(LED_BUILD_IN,!connected);
    }
    return connected;
}


void ros_init(){

  nh.initNode();
  
  nh.subscribe(subCmdRight);
  nh.subscribe(subCmdWheels);
  nh.subscribe(subCmdVel);
}