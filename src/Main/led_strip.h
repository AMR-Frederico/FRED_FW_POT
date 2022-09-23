#include <Main/config.h>
#include <Adafruit_NeoPixel.h>

Adafruit_NeoPixel pixels(NUMPIXELS, LED_STRIP, NEO_GRB + NEO_KHZ800);

class Led_strip
{
private:
    /* data */
public:
     Led_strip(/* args */);
     void on(int color);
     void off();
};

Led_strip::Led_strip(){
    pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
    pixels.setBrightness(100); // not so bright
}

void Led_strip::on(int color){

    pixels.fill(color);
    pixels.show();
    
}

void Led_strip::off(){
  pixels.fill(0x000000);
  pixels.show();
}