
#include <Main/config.h>

#include <Main/motor.h>
#include <Main/led_strip.h>

//@vel PWM signal between 0 and 1023 
// postive our negative representes de direction, positive been forward

motor motor1(M1_IN1 ,M1_IN2,M1_PWM,0);
motor motor2(M2_IN1 ,M2_IN2,M2_PWM,1);
motor motor3(M3_IN1 ,M3_IN2,M3_PWM,3);
motor motor4(M4_IN1 ,M4_IN2,M4_PWM,4);


//Global 

int pwm_right = 0 ;
int pwm_left = 0  ; 
float speed_linear ;
float speed_angular ; 

void stop(motor motor){
  digitalWrite(motor.In_A, HIGH);  
  digitalWrite(motor.In_B, HIGH);
  ledcWrite(motor.Canal ,0);
}


void write_PWM(motor motor, float vel){

  //satured output

  if(vel>=SATURATION){
    vel = SATURATION;
  }
  if(vel<= -SATURATION){
    vel = -SATURATION;
  }
  
  //send to H bridge 
  if(vel == 0){
    stop(motor);
  }
  else if(vel >= 0)
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

 float speed2pwm(float speed){
  //max_speed - max rpm
  //current_speed - desired rpm
  
  float desired_rpm = (MAX_RPM*speed)/MAX_SPEED ; 

  return desired_rpm ;
}






//receive the twsit msg and figure out the speed of each wheel 
void cmdVelCB( const geometry_msgs::Twist& twist)
{

  speed_angular = twist.angular.z;
  speed_linear  = twist.linear.x;

if(twist.linear.x > 10)
  led_strip_controler(1);

}

float getLinear(){
    return speed_linear;
}

float getAngular(){
    return speed_angular;
}

float cinematic_left(float linear, float angular,int gain){

  return gain*(linear - angular*L);
}

float cinematic_right(float linear, float angular,int gain){

  return gain*(linear + angular*L);
}

void write_all(int speed_left, int speed_right){

  pwm_left  = speed2pwm(speed_left);
  pwm_right = speed2pwm(speed_right);

  write_PWM(motor1,pwm_right);
  write_PWM(motor2,pwm_right);
  write_PWM(motor3,pwm_left);
  write_PWM(motor4,pwm_left);

}