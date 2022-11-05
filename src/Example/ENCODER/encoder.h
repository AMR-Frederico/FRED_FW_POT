/*........................
  Encoder Reading
  Author: Andre Henning
  Company: Control Robotics
 ...........................*/

#ifndef ENCODER_H // include guard
#define ENCODER_H
  
  #include <Arduino.h>

  class Encoder
  {
    public:
      void setup();
      static  void IRAM_ATTR interruptionChA();
      static  void IRAM_ATTR interruptionChB();
      double readAngle();
      double readRPM();
      void debugPrint();
      void reset();
        
    private:
    

  };

  
#endif