

#ifndef ENCODER__H // include guard
#define ENCODER__H
  //needs to be update like right encoder 
  #include <Arduino.h>

  class EncoderL
  {
    public:
      void setup();
      static  void IRAM_ATTR interruptionChL();
      double readAngle();
      double readRPM();
      double readTicks();
      void debugPrint();
      void reset();
        
    private:
    

  };

  
#endif