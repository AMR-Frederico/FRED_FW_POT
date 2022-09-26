

#ifndef __CONTROLER__H__
#define __CONTROLER__H__

#include <Main/config.h>
#include <std_msgs/Float32.h>
#include <Adafruit_NeoPixel.h>

Adafruit_NeoPixel  pixels(NUMPIXELS, LED_STRIP, NEO_GRB + NEO_KHZ800);
int long red = 0xFF0000 ;
int long off = 0x000000 ;
int long blue = 0x0000FF ;

void led_strip_init(){

    pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
    pixels.setBrightness(100); // not so bright

}

void led_strip_controler_ros(const std_msgs::Float32& msg){
    int color = msg.data;

    if(color != 0){
        pixels.fill(blue);
        pixels.show();
    }else{
        pixels.fill(0x000000);
        pixels.show();
    }
}

void led_strip_controler(int color){
   

    if(color != 0){
        pixels.fill(blue);
        pixels.show();
    }else{
        pixels.fill(0x000000);
        pixels.show();
    }
}
#endif  //!__CONTROLER__H__