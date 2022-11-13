

#ifndef ENCODER_H // include guard
#define ENCODER_H
  
  #include <Arduino.h>

  class EncoderR
  {
    public:
      void setup();
      static  void IRAM_ATTR interruptionChR();
      double readAngle();
      double readRPM();
      double readTicks();
      void debugPrint();
      void reset();
        
    private:
    

  };

  
#endif