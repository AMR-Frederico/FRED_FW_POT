#include <Main/config.h>


class controler
{
private:
    float proporcional();
    float integrative();
    float derivative();
public:
    float KP;
    float KD;
    float KI;
    float error;
    float time; 
    float output_value;

    controler(float kp, float kd, float ki);
    float output(float input_value, float current_value);


};

controler::controler(float kp, float kd, float ki)
{   KP = kp;
    KD = kd;
    KI = ki;
}

float controler::output(float input_value, float current_value){
    error = current_value - input_value;
    time = micros();
    output_value = proporcional();

}

float controler::proporcional(){
    return error*KP; 

}






