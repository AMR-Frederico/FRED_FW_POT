

#ifndef ENCODER_H // include guard
#define ENCODER_H
  
  #include <Arduino.h>

  class Encoder
  {
    public:
      Encoder(uint8_t pin_A,uint8_t pin_B);
      void setup();
      static  void IRAM_ATTR interruptionChA();
      static  void IRAM_ATTR interruptionChB();
      uint8_t DI_ENCODER_CH_A;
      uint8_t DI_ENCODER_CH_B;
      double readPulses();
      double readAngle();
      double readRPM();
      void debugPrint();
      void reset();
        
    private:
      

  };

  
#endif