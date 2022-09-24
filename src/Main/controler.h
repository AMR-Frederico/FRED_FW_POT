

#ifndef __CONTROLER__H__
#define __CONTROLER__H__

#include <Main/config.h>
#include <std_msgs/Int16.h>
#include <Adafruit_NeoPixel.h>

Adafruit_NeoPixel  pixels(NUMPIXELS, LED_STRIP, NEO_GRB + NEO_KHZ800);
// red = 0xFF0000


void led_strip_init(){

    pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
    pixels.setBrightness(100); // not so bright

}

void led_strip_controler(const std_msgs::Float32& msg){
    int color = msg.data;

    if(color != 0){
        pixels.fill(0xFF0000);
        pixels.show();
    }else{
        pixels.fill(0x000000);
        pixels.show();
    }
}
#endif  //!__CONTROLER__H__