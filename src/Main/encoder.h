

#ifndef ENCODER_H // include guard
#define ENCODER_H
  
  #include <Arduino.h>

  class Encoder
  {
    public:
      Encoder( int pin_A, int pin_B);
      void setup();
      void IRAM_ATTR interruptionChA();
      void IRAM_ATTR interruptionChB();
      int DI_ENCODER_CH_A;
      int DI_ENCODER_CH_B;
      double readPulses();
      double readAngle();
      double readRPM();
      void debugPrint();
      void reset();
        
    private:
      

  };

  
#endif