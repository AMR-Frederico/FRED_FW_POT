#include <Arduino.h>
volatile long temp, counter = 0; //This variable will increase or decrease depending on the rotation of encoder

#define CANAL_A 36
#define CANAL_B 39

void ai0() {
    // ai0 is activated if DigitalPin nr 2 is going from LOW to HIGH
    // Check pin 3 to determine the direction
    if(digitalRead(CANAL_A)==LOW) {
        counter++;
    }else{
        counter--;
    }
}
   
void ai1() {
    // ai0 is activated if DigitalPin nr 3 is going from LOW to HIGH
    // Check with pin 2 to determine the direction
    if(digitalRead(CANAL_B)==LOW) {
        counter--;
    }else{
        counter++;
    }
}

void setup() {
    Serial.begin (115200);

    pinMode(CANAL_A, INPUT); 
    pinMode(CANAL_B, INPUT);

    //A rising pulse from encodenren activated ai0(). AttachInterrupt 0 is DigitalPin nr 2 on moust Arduino.
    attachInterrupt(CANAL_A, ai0, RISING);
   
    //B rising pulse from encodenren activated ai1(). AttachInterrupt 1 is DigitalPin nr 3 on moust Arduino.
    attachInterrupt(CANAL_B, ai1, RISING);
}
   
void loop() {
    // Send the value of counter
    if( counter != temp ){
        Serial.println (counter);
        temp = counter;
    }
}
   