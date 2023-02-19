#include "profiler.h" // header in local directory



unsigned long current_time = 0;

static long last_time = 0;
static double speed_increment = 0;
double delta_time = 0;
double last_set = 0;



 double Profile::rampa(double set_speed, double acc ){
     current_time = millis();
    
     //if the set speed changed, recalculate
      // if(last_set!=set_speed){

         delta_time = (current_time-last_time); 
         speed_increment = (acc*(delta_time/1000));

   //   / }
      last_time = current_time;
      // last_set = set_speed;

      //rampa positive
     if(ramp_set_speed<set_speed){
         ramp_set_speed = ramp_set_speed + speed_increment; 
         if(ramp_set_speed>set_speed){
            ramp_set_speed = set_speed;
         }
     }
      //rampa negative
     if(ramp_set_speed>set_speed){
        ramp_set_speed = ramp_set_speed - speed_increment; 
         if(ramp_set_speed<set_speed){
            ramp_set_speed = set_speed;
         }
         
     }
     return ramp_set_speed;

 }

void Profile::debugPrint(double set_speed){
    Serial.print("Set Speed: ");
    Serial.print( set_speed);
    Serial.print("| Target Speed: ");
    Serial.print(ramp_set_speed);
    Serial.print("| Speed Increment: ");
    Serial.print(speed_increment);
    Serial.print("| Current Time: ");
    Serial.print(current_time);
    Serial.print("| Delta_time: ");
    Serial.print(delta_time);
   
    Serial.println();

 }