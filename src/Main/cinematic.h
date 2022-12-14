
#include <Main/config.h>
#include <geometry_msgs/Twist.h>

float speed_linear ;
float speed_angular ; 

int cmd_rpm; 

//receive the twsit msg and figure out the speed of each wheel 
void cmdVelCB( const geometry_msgs::Twist& twist)
{

  speed_angular = twist.angular.z;
  speed_linear  = twist.linear.x;


}

void cmdRPMCB(const std_msgs::Int16& msgs){
    cmd_rpm = msgs.data;

}

int getRPMsetpoint(){
    return cmd_rpm; 
}

float getLinear(){
    return speed_linear;
}

float getAngular(){
    return speed_angular;
}

//return left wheel speed in radians/sec 
float cinematic_left(float linear, float angular,float gain){

  return gain*(linear + angular*(L/2))/RADIUS;
}

//return right wheel speed in radians/sec 
float cinematic_right(float linear, float angular, float gain){

  return (linear -   (angular*(L/2)))/RADIUS;
}