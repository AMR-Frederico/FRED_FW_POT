#include <Arduino.h>
#include <geometry_msgs/Twist.h>
#include <Main/config.h>
#include <std_msgs/Int16.h>
#include <std_msgs/Float32.h>
 
//recieve comands already for each wheel 
void cmdLeftWheelCB( const std_msgs::Int16& msg)
{
  if(msg.data >= 0)
  {
    
    ledcWrite(CANAL_M2,msg.data);
    digitalWrite(M2_IN1, LOW);
    digitalWrite(M2_IN2, HIGH);  
  }
  else
  {
    ledcWrite(CANAL_M2,-msg.data);
    digitalWrite(M2_IN1, HIGH);
    digitalWrite(M2_IN2, LOW);
  }
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
  float left_wheel_data = gain*(twist.linear.x - twist.angular.z*L);
  float right_wheel_data = gain*(twist.linear.x + twist.angular.z*L);
  
  if(left_wheel_data >= 0)
  { 
    ledcWrite(CANAL_M2,abs(left_wheel_data));
    digitalWrite(M2_IN1, LOW);
    digitalWrite(M2_IN2, HIGH); 

    ledcWrite(CANAL_M1,abs(left_wheel_data));
    digitalWrite(M1_IN1, LOW);
    digitalWrite(M1_IN2, HIGH);  
  }
  else
  {
    ledcWrite(CANAL_M2,abs(left_wheel_data));
    digitalWrite(M2_IN1, HIGH);
    digitalWrite(M2_IN2, LOW);

    ledcWrite(CANAL_M1,abs(left_wheel_data));
    digitalWrite(M1_IN1, HIGH);
    digitalWrite(M1_IN2, LOW);
  }
  if(right_wheel_data >= 0)
  {
    ledcWrite(CANAL_M3,abs(right_wheel_data));
    digitalWrite(M3_IN1, LOW);
    digitalWrite(M3_IN2, HIGH); 
    ledcWrite(CANAL_M4,abs(right_wheel_data));
    digitalWrite(M4_IN1, LOW);
    digitalWrite(M4_IN2, HIGH);  
  }
  else
  {
    ledcWrite(CANAL_M3,abs(right_wheel_data));
    digitalWrite(M3_IN1, HIGH);
    digitalWrite(M3_IN2, LOW);
    ledcWrite(CANAL_M4,abs(right_wheel_data));
    digitalWrite(M4_IN1, HIGH);
    digitalWrite(M4_IN2, LOW);
  }
}