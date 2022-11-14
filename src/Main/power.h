
#include <Main/config.h>

#include <Main/motor.h>
#include <Main/led_strip.h>


// fred(linear(m/s),angular(rad/s)) -> |cinematic| -> wheel(angular(rad/s)) -> |angular2rpm| -> wheel(angular(rpm)) -> |rpm2pwm| -> wheel(pwm)

//@vel PWM signal between 0 and 1023 
// postive our negative representes de direction, positive been forward

motor motor1(M1_IN1 ,M1_IN2,M1_PWM,0);
motor motor2(M2_IN1 ,M2_IN2,M2_PWM,1);
motor motor3(M3_IN1 ,M3_IN2,M3_PWM,3);
motor motor4(M4_IN1 ,M4_IN2,M4_PWM,4);

bool debug = false;
//Global 

int pwm_right = 0 ;
int pwm_left = 0  ; 
float rpm_right = 0 ;
float rpm_left = 0;

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
  if(vel >= -MIN_PWM && vel <= MIN_PWM){

    if(debug)
    led_strip_controler(2);
    stop(motor);
  }
  else if(vel >= 0)
  { if(debug)
    led_strip_controler(0);
    ledcWrite(motor.Canal ,vel);
    digitalWrite(motor.In_B, LOW);
    digitalWrite(motor.In_A, HIGH);  
  }
  else
  {  if(debug)
    led_strip_controler(0);
     ledcWrite(motor.Canal,vel);
     digitalWrite(motor.In_B, HIGH);
     digitalWrite(motor.In_A, LOW);
  }
}

 int rpm2pwm(float speed_rpm){
  //scale convertion 
  // rpm - min_rpm     pwm - min_pwm
  // ------   =   --------------
  // max_rpm     max_pwm - min_pwm

  

  float desired_pwm = 0;

  desired_pwm = (((abs(speed_rpm) - MIN_RPM)*(MAX_PWM-MIN_PWM))/(MAX_RPM - MIN_RPM )) + MIN_PWM ;

  if(speed_rpm <= 0 )
    desired_pwm = desired_pwm*(-1);


  return desired_pwm;
}

 float angular2rpm(float speed_angular){
  //convert from angular w to rpm 
  
  float desired_rpm = (speed_angular*60)/(2*PI)  ;

  return desired_rpm;
}





//receive the twsit msg and figure out the speed of each wheel 
void cmdVelCB( const geometry_msgs::Twist& twist)
{

  speed_angular = twist.angular.z;
  speed_linear  = twist.linear.x;


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


//recieve angular
void write_all(int angular_speed_left, int angular_speed_right){

  rpm_left = angular2rpm(angular_speed_left);
  rpm_right = angular2rpm(angular_speed_right);

  pwm_left  = rpm2pwm(rpm_left);
  pwm_right = rpm2pwm(rpm_right);

  write_PWM(motor1,pwm_right);
  write_PWM(motor2,pwm_right);
  write_PWM(motor3,pwm_left);
  write_PWM(motor4,pwm_left);

}