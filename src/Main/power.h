#include <Arduino.h>
#include <geometry_msgs/Twist.h>
#include <Main/config.h>
#include <std_msgs/Int16.h>
#include <std_msgs/Float32.h>

//@vel PWM signal between 0 and 1023 
// postive our negative representes de direction, positive been forward

void right_PWM(int CANAL,int IN1,int IN2, float vel){

  if(vel>=SATURATION){
    vel = SATURATION;
  }
  if(vel<= -SATURATION){
    vel = -SATURATION;
  }
  
    if(vel >= 0)
  {
    ledcWrite(CANAL,vel);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);  
  }
  else
  {
     ledcWrite(CANAL,vel);
     digitalWrite(IN1, HIGH);
     digitalWrite(IN2, LOW);
  }
}

void cmdWheelsCB( const std_msgs::Int16& msg)
{
  right_PWM(CANAL_M1,M1_IN1,M1_IN2,msg.data);
  right_PWM(CANAL_M2,M2_IN1,M2_IN2,msg.data);
  right_PWM(CANAL_M3,M3_IN1,M3_IN2,msg.data);
  right_PWM(CANAL_M4,M4_IN1,M4_IN2,msg.data);
}

void cmdRightWheelCB( const std_msgs::Int16& msg)
{
  
  if(msg.data >= 0)
  {
    ledcWrite(CANAL_M3,msg.data);
    digitalWrite(M3_IN1, LOW);
    digitalWrite(M3_IN2, HIGH);  
  }
  else
  {
     ledcWrite(CANAL_M3,msg.data);
     digitalWrite(M3_IN1, HIGH);
     digitalWrite(M3_IN2, LOW);
  }
}

void stop(){
    digitalWrite(M2_IN1,LOW);
    digitalWrite(M2_IN2,LOW);
    digitalWrite(M3_IN1,LOW);
    digitalWrite(M3_IN2,LOW); 

    ledcWrite(CANAL_M2,0);
    ledcWrite(CANAL_M3,0);
}


//receive the twsit msg and figure out the speed of each wheel 
void cmdVelCB( const geometry_msgs::Twist& twist)
{
  int gain = 1;
 
  float left_wheel_data  = gain*(twist.linear.x - twist.angular.z*L);
  float right_wheel_data = gain*(twist.linear.x + twist.angular.z*L);

  
  
  if(left_wheel_data >= 0)
  { 
    ledcWrite(CANAL_M2,abs(left_wheel_data));
    digitalWrite(M2_IN1, HIGH);
    digitalWrite(M2_IN2, LOW); 

    ledcWrite(CANAL_M1,abs(left_wheel_data));
    digitalWrite(M1_IN1, HIGH);
    digitalWrite(M1_IN2, LOW);  
  }
  else
  {
    ledcWrite(CANAL_M2,abs(left_wheel_data));
    digitalWrite(M2_IN1, LOW);
    digitalWrite(M2_IN2, HIGH);

    ledcWrite(CANAL_M1,abs(left_wheel_data));
    digitalWrite(M1_IN1, LOW);
    digitalWrite(M1_IN2, HIGH);
  }
  if(right_wheel_data >= 0)
  {
    ledcWrite(CANAL_M3,abs(right_wheel_data));
    digitalWrite(M3_IN1, HIGH);
    digitalWrite(M3_IN2, LOW); 
    ledcWrite(CANAL_M4,abs(right_wheel_data));
    digitalWrite(M4_IN1, HIGH);
    digitalWrite(M4_IN2, LOW);  
  }
  else
  {
    ledcWrite(CANAL_M3,abs(right_wheel_data));
    digitalWrite(M3_IN1, LOW);
    digitalWrite(M3_IN2, HIGH);
    ledcWrite(CANAL_M4,abs(right_wheel_data));
    digitalWrite(M4_IN1, LOW);
    digitalWrite(M4_IN2, HIGH);
  }

   
}