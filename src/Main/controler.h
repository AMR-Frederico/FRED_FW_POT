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
    float time; 
    float output_value;

    Controler(float kp, float kd, float ki);
    float output(float input_value, float current_value);


};
#endif



