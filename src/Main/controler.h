#include <Main/config.h>

double rampa_set_speed = 0;
static long current_time = 0 ;
static long last_time = 0 ;
double delta_time = 0; 
double last_set = 0; 
double speed_incriment = 0;

// Add a ramp to the speed -> gradual accelaration and gradual stop

double rampa_profiler(double set_speed, double acc){
    current_time = millis();

    delta_time = (current_time-last_time);
    speed_incriment = (acc*(delta_time/1000));

    last_time = current_time;

    if(rampa_set_speed < set_speed){
        rampa_set_speed = rampa_set_speed + speed_incriment;
        if(rampa_set_speed>set_speed){
            rampa_set_speed = set_speed;
        } 
    }
    if(rampa_set_speed > set_speed){
        rampa_set_speed = rampa_set_speed - speed_incriment;
        if(rampa_set_speed<set_speed){
            rampa_set_speed = set_speed;
        } 
    }

    return rampa_set_speed ;
}