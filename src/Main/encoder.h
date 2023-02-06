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
      Encoder(int pin_A,int pin_B);
      void setup();
      static  void IRAM_ATTR interruptionChA();
      static  void IRAM_ATTR interruptionChB();
      volatile int DI_ENCODER_CH_A;
      volatile int DI_ENCODER_CH_B;
      double readPulses();
      double readAngle();
      double readRPM();
      void debugPrint();
      void reset();
        
    private:
      

  };

  
#endif