#include <ros.h>
#include <std_msgs/Int16.h>
#include <std_msgs/Float32.h>
#include <geometry_msgs/Twist.h>

#include <Arduino.h>

#include <Main/config.h>
#include <Main/ros_com.h>
#include <Main/power.h>


bool _connect = false ;


ros::NodeHandle  nh;

ros::Subscriber<std_msgs::Int16> subCmdWheels("cmd_wheels", cmdWheelsCB );
ros::Subscriber<std_msgs::Int16> subCmdRight("cmd_right_wheel",cmdRightWheelCB );

ros::Subscriber<geometry_msgs::Twist> subCmdVel("cmd_vel", cmdVelCB);


void setup() {
  //------------motors  
  pinMode(M2_PWM, OUTPUT);//Definimos os pinos  como saída.
  pinMode(M3_PWM, OUTPUT);
  
  ledcAttachPin(M2_PWM, CANAL_M2);//Atribuimos o pino M2_PWM ao canal 0.
  ledcAttachPin(M3_PWM, CANAL_M3);//Atribuimos o pino M3_PWM ao canal 1.
  ledcSetup(CANAL_M2,  FREQUENCIA, 10);//Atribuimos ao canal 0 a frequencia de 1000Hz com resolucao de 10bits.
  ledcSetup(CANAL_M3, FREQUENCIA, 10);//Atribuimos ao canal 0 a frequencia de 1000Hz com resolucao de 10bits.

  //------------motors  
  pinMode(M1_PWM, OUTPUT);//Definimos os pinos  como saída.
  pinMode(M4_PWM, OUTPUT);
  
  ledcAttachPin(M1_PWM, CANAL_M1);//Atribuimos o pino M2_PWM ao canal 0.
  ledcAttachPin(M4_PWM, CANAL_M4);//Atribuimos o pino M3_PWM ao canal 1.
  ledcSetup(CANAL_M1, FREQUENCIA, 10);//Atribuimos ao canal 0 a frequencia de 1000Hz com resolucao de 10bits.
  ledcSetup(CANAL_M4, FREQUENCIA, 10);//Atribuimos ao canal 0 a frequencia de 1000Hz com resolucao de 10bits.

  //-------------DIGITAL------------------
  pinMode(M1_IN2,OUTPUT);
  pinMode(M1_IN1,OUTPUT);

  pinMode(M2_IN1,OUTPUT);
  pinMode(M2_IN2,OUTPUT);

  pinMode(M3_IN1,OUTPUT);
  pinMode(M3_IN2,OUTPUT);

  pinMode(M4_IN1,OUTPUT);
  pinMode(M4_IN2,OUTPUT);
  
  pinMode(LED_BUILD_IN,OUTPUT);
  digitalWrite(LED_BUILD_IN,HIGH);
  
  nh.initNode();
  nh.subscribe(subCmdRight);
  nh.subscribe(subCmdWheels);
  nh.subscribe(subCmdVel);


 

}

void loop() 
{   
    
    if(!rosConnected(nh,_connect))
        stop();
  
    nh.spinOnce();

}
