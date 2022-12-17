#include "controler.h"
// #include <Main/tools.h>

Controler::Controler(float kp, float kd, float ki)
{   KP = kp;
    KD = kd;
    KI = ki;
    integral = 0;
    time = 0 ; 
    last_time = 0 ;
    delta_time= 0 ;
}

float Controler::output(float input_value, float current_value){
    error =  input_value - current_value ;
    time = micros();
    delta_time = time - last_time + 10;

    output_value =  proporcional() + integrative();

    // output_value = saturation(output_value,1000);

    last_time = time;
    return output_value;
}

float Controler::proporcional(){

    return error*KP; 

}

float Controler::integrative(){
    integral = delta_time*error*KI ;
    // integral = saturation(integral,1000);
    return integral ;

}







