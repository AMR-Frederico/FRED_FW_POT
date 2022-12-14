#include "controler.h"

Controler::Controler(float kp, float kd, float ki)
{   KP = kp;
    KD = kd;
    KI = ki;
}

float Controler::output(float input_value, float current_value){
    error =  input_value - current_value ;
    time = micros();
    output_value =  proporcional();
    return output_value;
}

float Controler::proporcional(){
    return error*KP; 

}






