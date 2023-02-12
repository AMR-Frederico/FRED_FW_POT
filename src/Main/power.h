


#include <Main/motor.h>
#include <Main/tools.h>

// fred(linear(m/s),angular(rad/s)) -> |cinematic| -> wheel(angular(rad/s)) -> |angular2rpm| -> wheel(angular(rpm)) -> |rpm2pwm| -> wheel(pwm)

//@vel PWM signal between 0 and 1023 
// postive our negative representes de direction, positive been forward

motor motor1(M1_IN1 ,M1_IN2,M1_PWM,0);
motor motor2(M2_IN1 ,M2_IN2,M2_PWM,1);
motor motor3(M3_IN1 ,M3_IN2,M3_PWM,3);
motor motor4(M4_IN1 ,M4_IN2,M4_PWM,4);


//Global 

int pwm_right = 0 ;
int pwm_left = 0  ; 
int pwm_motor = 0;



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



void write2motors(int rpm_left, int rpm_right){

  pwm_left  = rpm2pwm(rpm_left);
  pwm_right = rpm2pwm(rpm_right);

  pwm_left = saturation_under(pwm_left,PWM_SATURATION_UNDER);
  pwm_right = saturation_under(pwm_right,PWM_SATURATION_UNDER);

  write_PWM(motor1,pwm_left); 
  write_PWM(motor2,pwm_right); 
  write_PWM(motor3,pwm_right); 
  write_PWM(motor4,pwm_left); 

}


void write2motor(int rpm,int motor){
  pwm_motor = rpm2pwm(rpm);

  switch (motor)  {
    case 1:
       write_PWM(motor1,pwm_motor);
        break;

    case 2:
       write_PWM(motor2,pwm_motor);
        break;
    case 3:
       write_PWM(motor3,pwm_motor);
        break;
     case 4:
       write_PWM(motor4,pwm_motor);
        break;
    default:
          write_PWM(motor1,pwm_motor);
}

}




