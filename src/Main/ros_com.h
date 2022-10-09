#include <ros.h>
#include <std_msgs/Int16.h>
#include <std_msgs/Float32.h>
#include <geometry_msgs/Twist.h>

#include <Main/power.h>
#include <Main/led_strip.h>

// Subscribers ------------
#define cmd_wheels_topic "cmd_wheels"
#define cmd_right_wheel_topic "cmd_right_wheel"
#define cmd_vel_topic "cmd_vel"
#define cmd_led_strip_topic "cmd/led_strip/color"

//Publisher 
#define pwm_right_topic "power/status/pwm/right"
#define pwm_left_topic "power/status/pwm/left"


ros::NodeHandle  nh;

//locomotion 
ros::Subscriber<geometry_msgs::Twist> subCmdVel(cmd_vel_topic, cmdVelCB);
//lights 
ros::Subscriber<std_msgs::Float32> subLedStrip(cmd_led_strip_topic, led_strip_controler_ros );

std_msgs::Int16 pwmRightMsg ;
ros::Publisher subPwmRight(pwm_right_topic, &pwmRightMsg);

std_msgs::Int16 pwmLeftMsg ;
ros::Publisher subPwmLeft(pwm_left_topic, &pwmLeftMsg);

bool rosConnected(ros::NodeHandle  nh,bool _connect){
    bool connected = nh.connected();
    if(_connect != connected){
        _connect = connected;
        digitalWrite(LED_BUILD_IN,!connected);
        led_strip_controler(1);
    }
    else{
        led_strip_controler(0);
    }
    return connected;
}


void ros_init(){

  nh.initNode();

  nh.subscribe(subCmdVel);
  nh.subscribe(subLedStrip);

  nh.advertise(subPwmRight);
  nh.advertise(subPwmLeft);
}

void ros_loop(){
    pwmRightMsg.data = pwm_right;
    subPwmRight.publish(&pwmRightMsg);

    pwmLeftMsg.data = pwm_left;
    subPwmLeft.publish(&pwmLeftMsg);
}