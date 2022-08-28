#include <ros.h>
#include <std_msgs/Int16.h>
#include <std_msgs/Float32.h>
#include <geometry_msgs/Twist.h>
#include <Arduino.h>

#include <Main/config.h>

#define LOOP_TIME   200000  
#define CANAL_R  0
#define CANAL_L  1
#define PWM_MIM 150
#define PWM_MAX 1023
#define SATURATION 1020

int L = DISTANCE;


bool _connect = false ;


ros::NodeHandle  nh;
std_msgs::Float32 left_wheel_vel;
ros::Publisher left_wheel_vel_pub("/left_wheel_velocity", &left_wheel_vel);

std_msgs::Float32 right_wheel_vel;
ros::Publisher right_wheel_vel_pub("/right_wheel_velocity", &right_wheel_vel);



bool rosConnected(){
    bool connected = nh.connected();
    if(_connect != connected){
        _connect = connected;
        digitalWrite(LED_BUILD_IN,!connected);
    }
    return connected;
}



//  void timerIsr()
// {
//     //stop the timer
//   //Left Motor Speed 
//     left_wheel_vel.data = float(counter_left)*((2*pi*RADIUS)/TICKS);
//     left_wheel_vel_pub.publish(&left_wheel_vel);
//     right_wheel_vel.data = float(counter_right)*((2*pi*RADIUS)/TICKS);
//     right_wheel_vel_pub.publish(&right_wheel_vel);
//     sensor_vel.linear.x = radius*(left_wheel_vel.data + right_wheel_vel.data)/2;
//     sensor_vel.linear.y = 0;
//     sensor_vel.linear.z = 0;
//     sensor_vel.angular.x = 0;
//     sensor_vel.angular.y = 0;
//     sensor_vel.angular.z = radius*(left_wheel_vel.data + right_wheel_vel.data)/L;
//     sensor_vel_pub.publish(&sensor_vel);
//     counter_right=0;
//     counter_left=0;
 
// }
 
//recieve comands already for each wheel 
void cmdLeftWheelCB( const std_msgs::Int16& msg)
{
  if(msg.data >= 0)
  {
    
    ledcWrite(CANAL_L,msg.data);
    digitalWrite(M2_IN1, LOW);
    digitalWrite(M2_IN2, HIGH);  
  }
  else
  {
    ledcWrite(CANAL_L,-msg.data);
    digitalWrite(M2_IN1, HIGH);
    digitalWrite(M2_IN2, LOW);
  }
}

void cmdRightWheelCB( const std_msgs::Int16& msg)
{
  
  if(msg.data >= 0)
  {
    ledcWrite(CANAL_R,msg.data);
    digitalWrite(M3_IN1, LOW);
    digitalWrite(M3_IN2, HIGH);  
  }
  else
  {
     ledcWrite(CANAL_R,msg.data);
     digitalWrite(M3_IN1, HIGH);
     digitalWrite(M3_IN2, LOW);
  }
}

void stop(){
    digitalWrite(M2_IN1,LOW);
    digitalWrite(M2_IN2,LOW);
    digitalWrite(M3_IN1,LOW);
    digitalWrite(M3_IN2,LOW); 

    ledcWrite(CANAL_L,0);
    ledcWrite(CANAL_R,0);
}

ros::Subscriber<std_msgs::Int16> subCmdLeft("cmd_left_wheel", cmdLeftWheelCB );
ros::Subscriber<std_msgs::Int16> subCmdRight("cmd_right_wheel",cmdRightWheelCB );

//receive the twsit msg and figure out the speed of each wheel 
void cmdVelCB( const geometry_msgs::Twist& twist)
{
  int gain = 1;
  float left_wheel_data = gain*(twist.linear.x - twist.angular.z*L);
  float right_wheel_data = gain*(twist.linear.x + twist.angular.z*L);
  if(left_wheel_data >= 0)
  { 
    ledcWrite(CANAL_L,abs(left_wheel_data));
    digitalWrite(M2_IN1, LOW);
    digitalWrite(M2_IN2, HIGH);  
  }
  else
  {
    ledcWrite(CANAL_L,abs(left_wheel_data));
    digitalWrite(M2_IN1, HIGH);
    digitalWrite(M2_IN2, LOW);
  }
  if(right_wheel_data >= 0)
  {
    ledcWrite(CANAL_R,abs(right_wheel_data));
    digitalWrite(M3_IN1, LOW);
    digitalWrite(M3_IN2, HIGH);  
  }
  else
  {
     ledcWrite(CANAL_R,abs(right_wheel_data));
    digitalWrite(M3_IN1, HIGH);
    digitalWrite(M3_IN2, LOW);
  }
}
ros::Subscriber<geometry_msgs::Twist> subCmdVel("cmd_vel", cmdVelCB);


void setup() {
  //------------motors  
  pinMode(M2_PWM, OUTPUT);//Definimos os pinos  como saída.
  pinMode(M3_PWM, OUTPUT);
  
  ledcAttachPin(M2_PWM, CANAL_R);//Atribuimos o pino M2_PWM ao canal 0.
  ledcAttachPin(M3_PWM, CANAL_L);//Atribuimos o pino M3_PWM ao canal 1.
  ledcSetup(CANAL_R, 1000, 10);//Atribuimos ao canal 0 a frequencia de 1000Hz com resolucao de 10bits.
  ledcSetup(CANAL_L, 1000, 10);//Atribuimos ao canal 0 a frequencia de 1000Hz com resolucao de 10bits.

  //-------------DIGITAL------------------

  pinMode(M2_IN1,OUTPUT);
  pinMode(M2_IN2,OUTPUT);
  pinMode(M3_IN1,OUTPUT);
  pinMode(M3_IN2,OUTPUT);
  
  pinMode(LED_BUILD_IN,OUTPUT);
  digitalWrite(LED_BUILD_IN,HIGH);


  //Setup for encoders
 
  timer = timerBegin(0, 80, true);                //Begin timer with 1 MHz frequency (80MHz/80)
  timerAttachInterrupt(timer, &onTimer, true);   //Attach the interrupt to Timer1
  unsigned int timerFactor = 1000000/SamplingRate; //Calculate the time interval between two readings, or more accurately, the number of cycles between two readings
  timerAlarmWrite(timer, timerFactor, true);      //Initialize the timer
  timerAlarmEnable(timer); 
  
  nh.initNode();
  nh.subscribe(subCmdRight);
  nh.subscribe(subCmdLeft);
  nh.subscribe(subCmdVel);


 

}

void loop() 
{   
    if(interruptbool1)
    {
      analogRead(36);
      interruptbool1 = false;
    }
     if(!rosConnected())
        stop();
    
 
    


    
   

  
    nh.spinOnce();

}
