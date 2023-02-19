#ifndef PROFILER_H // include guard
#define PROFILER_H

  #include <Arduino.h>

  class Profile{
  public:
     
     
      double rampa(double set_speed, double acc );
      void debugPrint(double set_speed);
  private:
      double ramp_set_speed; 
  };

#endif