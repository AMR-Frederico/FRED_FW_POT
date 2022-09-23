#include <ros.h>
#include <std_msgs/Int16.h>
#include <std_msgs/Float32.h>
#include <geometry_msgs/Twist.h>

#include <Main/power.h>


// Subscribers ------------
#define cmd_wheels_topic "cmd_wheels"
#define cmd_right_wheel_topic "cmd_right_wheel"
#define cmd_vel_topic "cmd_vel"

//Publisher 
#define pwm_right_topic "power/status/pwm/right"
#define pwm_left_topic "power/status/pwm/left"

ros::NodeHandle  nh;

ros::Subscriber<std_msgs::Int16> subCmdWheels(cmd_wheels_topic, cmdWheelsCB );
ros::Subscriber<std_msgs::Int16> subCmdRight(cmd_right_wheel_topic,cmdRightWheelCB );
ros::Subscriber<geometry_msgs::Twist> subCmdVel(cmd_vel_topic, cmdVelCB);


std_msgs::Int16 pwmRightMsg ;
ros::Publisher subPwmRight(pwm_right_topic, &pwmRightMsg);

std_msgs::Int16 pwmLeftMsg ;
ros::Publisher subPwmLeft(pwm_left_topic, &pwmLeftMsg);

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

  nh.advertise(subPwmRight);
  nh.advertise(subPwmLeft);
}

void ros_loop(){
    pwmRightMsg.data = pwm_right;
    subPwmRight.publish(&pwmRightMsg);

    pwmLeftMsg.data = pwm_left;
    subPwmLeft.publish(&pwmLeftMsg);
}