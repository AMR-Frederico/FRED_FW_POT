
#include <Main/config.h>

#include <Main/motor.h>
#include <Main/led_strip.h>

//@vel PWM signal between 0 and 1023 
// postive our negative representes de direction, positive been forward

motor motor1(M1_IN1 ,M1_IN2,M1_PWM,0);
motor motor2(M2_IN1 ,M2_IN2,M2_PWM,1);
motor motor3(M3_IN1 ,M3_IN2,M3_PWM,3);
motor motor4(M4_IN1 ,M4_IN2,M4_PWM,4);

int pwm_right = 0 ;
int pwm_left = 0 ; 

void write_PWM(motor motor, float vel){

  //satured output

  if(vel>=SATURATION){
    vel = SATURATION;
  }
  if(vel<= -SATURATION){
    vel = -SATURATION;
  }
  
  //send to H bridge 

    if(vel >= 0)
  {
    ledcWrite(motor.Canal ,vel);
    digitalWrite(motor.In_B, LOW);
    digitalWrite(motor.In_A, HIGH);  
  }
  else
  {
     ledcWrite(motor.Canal,vel);
     digitalWrite(motor.In_B, HIGH);
     digitalWrite(motor.In_A, LOW);
  }
}

int speed2pwm(int speed){
  //max_speed - max rpm
  //current_speed - desired rpm
  
  int desired_rpm = (MAX_RPM*speed)/MAX_SPEED ; 

  return desired_rpm ;
}


void cmdWheelsCB( const std_msgs::Int16& msg)
{
 
}

void cmdRightWheelCB( const std_msgs::Int16& msg)
{
  
  
}

void stop(){
  write_PWM(motor1,0);
  write_PWM(motor2,0);
  write_PWM(motor3,0);
  write_PWM(motor4,0);
}


//receive the twsit msg and figure out the speed of each wheel 
void cmdVelCB( const geometry_msgs::Twist& twist)
{
  int gain = 1;
  
  //figure out speed for each wheell 
  //figure out speed in m/s for each wheel 
  float left_wheel_data  = gain*(twist.linear.x - twist.angular.z*L);
  float right_wheel_data = gain*(twist.linear.x + twist.angular.z*L);

  //convert speed from m/s to pwm 
  pwm_left  = speed2pwm(left_wheel_data);
  pwm_right = speed2pwm(right_wheel_data);

if(twist.linear.x > 10)
  led_strip_controler(1);

  write_PWM(motor1,pwm_right);
  write_PWM(motor2,pwm_right);
  write_PWM(motor3,pwm_left);
  write_PWM(motor4,pwm_left);
}