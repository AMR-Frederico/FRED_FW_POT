#include <ros.h>
#include <std_msgs/Int32.h>
#include <std_msgs/Int16.h>
#include <std_msgs/Float32.h>
#include <geometry_msgs/Twist.h>

#include <Main/cinematic.h>
#include <Main/power.h>
#include <Main/led_strip.h>

// Subscribers ------------
#define cmd_wheels_topic "cmd_wheels"
#define cmd_rpm_topic "cmd/rpm"
#define cmd_vel_topic "cmd_vel/safe"
#define cmd_led_strip_topic "cmd/led_strip/color"

//Publisher 
#define pwm_right_topic "power/status/pwm/right"
#define pwm_left_topic "power/status/pwm/left"

#define angular_speed_right_topic "power/status/speed/angular/right"
#define angular_speed_left_topic "power/status/speed/angular/left"

#define rpm_speed_right_topic "power/status/speed/rpm/right"
#define rpm_speed_left_topic "power/status/speed/rpm/left"

#define ticks_left_topic "power/status/distance/ticks/left"
#define ticks_right_topic "power/status/distance/ticks/right"

//debug
#define rpm_controled_topic "power/status/debug/controler/rpm"
#define pwm_debug_topic "power/status/debug/pwm"



ros::NodeHandle  nh;

//------------------SUBS--------------------
//locomotion 
ros::Subscriber<geometry_msgs::Twist> subCmdVel(cmd_vel_topic, cmdVelCB);
ros::Subscriber<std_msgs::Int16> subCmd_RPM(cmd_rpm_topic, cmdRPMCB); 
//lights 
ros::Subscriber<std_msgs::Float32> subLedStrip(cmd_led_strip_topic, led_strip_controler_ros );


//-----------------PUBS-------------------------

std_msgs::Int16 pwmRightMsg ;
ros::Publisher subPwmRight(pwm_right_topic, &pwmRightMsg);

std_msgs::Int16 pwmLeftMsg ;
ros::Publisher subPwmLeft(pwm_left_topic, &pwmLeftMsg);

std_msgs::Float32 angularSpeedRightMsg ;
ros::Publisher subAngularSpeedRight(angular_speed_right_topic, &angularSpeedRightMsg);

std_msgs::Float32 angularSpeedLeftMsg ;
ros::Publisher subAngularSpeedLeft(angular_speed_left_topic, &angularSpeedLeftMsg);

std_msgs::Float32 rpmSpeedLeftMsg ;
ros::Publisher subRpmSpeedLeft(rpm_speed_left_topic, &rpmSpeedLeftMsg);

std_msgs::Float32 rpmSpeedRightMsg ;
ros::Publisher subRpmSpeedRight(rpm_speed_right_topic, &rpmSpeedRightMsg);

std_msgs::Float32 ticksRightMsg ;
ros::Publisher subTicksRight(ticks_right_topic, &ticksRightMsg);

std_msgs::Float32 ticksLeftMsg ;
ros::Publisher subTicksLeft(ticks_left_topic, &ticksLeftMsg);

std_msgs::Float32 rpmControledMsg ;
ros::Publisher subControledRPM(rpm_controled_topic, &rpmControledMsg);
std_msgs::Float32 pwmMsg ;
ros::Publisher subPwm(pwm_debug_topic, &pwmMsg);


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

  nh.subscribe(subCmdVel);
  nh.subscribe(subLedStrip);
  nh.subscribe(subCmd_RPM);


  nh.advertise(subPwmRight);
  nh.advertise(subPwmLeft);

  nh.advertise(subAngularSpeedRight);
  nh.advertise(subAngularSpeedLeft);
  
  nh.advertise(subRpmSpeedLeft);
  nh.advertise(subRpmSpeedRight);

  nh.advertise(subTicksLeft);
  nh.advertise(subTicksRight);

  nh.advertise(subControledRPM);
  nh.advertise(subPwm);
}

void ros_loop(float speed_right, float speed_left,double angle_encoder_read_left, double angle_encoder_read_right,double rpm_encoder_read_left ,double rpm_encoder_read_right,double ticks_encoder_read_left,double ticks_encoder_read_right, float rpm_controled){
    pwmRightMsg.data = pwm_right;
    subPwmRight.publish(&pwmRightMsg);

    pwmLeftMsg.data = pwm_left;
    subPwmLeft.publish(&pwmLeftMsg);

    angularSpeedLeftMsg.data = angle_encoder_read_left;
    subAngularSpeedLeft.publish(&angularSpeedLeftMsg);


    angularSpeedRightMsg.data = angle_encoder_read_right;
    subAngularSpeedRight.publish(&angularSpeedRightMsg);

    rpmSpeedLeftMsg.data = rpm_encoder_read_left;
    subRpmSpeedLeft.publish(&rpmSpeedLeftMsg);

    rpmSpeedRightMsg.data = rpm_encoder_read_right;
    subRpmSpeedRight.publish(&rpmSpeedRightMsg);

    ticksRightMsg.data = ticks_encoder_read_right;
    subTicksRight.publish(&ticksRightMsg);

    ticksLeftMsg.data = ticks_encoder_read_left;
    subTicksLeft.publish(&ticksLeftMsg);

    rpmControledMsg.data = rpm_controled;
    subControledRPM.publish(&rpmControledMsg);
    pwmMsg.data = pwm_motor;
    subPwm.publish(&pwmMsg);


}