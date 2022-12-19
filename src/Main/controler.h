#include <Main/config.h>
#ifndef CONTROLER // include guard
#define CONTROLER

class Controler
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
    float last_error;
    float delta_error;
    float output_value;
    float integral;
    unsigned long time; 
    unsigned long last_time;
    unsigned long  delta_time;

    Controler(float kp, float kd, float ki);
    float output(float input_value, float current_value);


};
#endif



