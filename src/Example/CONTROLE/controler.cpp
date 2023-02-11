#include "controler.h"
// #include <Main/tools.h>

Controler::Controler(float kp,float ki, float kd)
{   KP = kp;
    KD = kd;
    KI = ki;
    integral = 0;
    time = 0 ; 
    last_time = 0 ;
    delta_time= 0 ;
    last_error = 0;
    error = 0;
}

float Controler::output(float input_value, float current_value){
    input_values = input_value;
    current_values = current_value;
    error =  input_value - current_value ;
    time = micros();
    delta_time = time - last_time;
    if(input_value == 0){
        output_value =  input_value + proporcional() + derivative() ;
    }else{
        output_value =  input_value +proporcional() + integrative() + derivative();
    }

    // output_value = saturation(output_value,1000);

    last_time = time;
    return output_value;
}

float Controler::proporcional(){

    return error*KP; 

}

float Controler::integrative(){
    integral = integral + (error*(delta_time/1000000));
    // integral = saturation(integral,1000);
    return integral*KI;

}

float Controler::derivative(){
    delta_error = (last_error - error);
    return delta_error*KD;

}

void Controler::debug(){
    
     Serial.print(" |delta_time: ");
    Serial.print(delta_time);

    Serial.print(" |input_values: ");
    Serial.print(input_values);
    Serial.print(" |current_values: ");
    Serial.print(current_values);

    Serial.print(" ||error: ");
    Serial.print(error);
    Serial.print(" |P: ");
    Serial.print(proporcional());
    Serial.print(" |I: ");
    Serial.print(error*KI*(delta_time/10000)/10,10);
    Serial.print(" |D: ");
    Serial.print(derivative());

    Serial.print(" |output_value: ");
    Serial.print(output_value);
    Serial.println("");

}





