
#include "encoderR.h" // header in local directory
#include "config.h"

//--------------------------------------------------
//Pinout
//--------------------------------------------------
volatile int DI_ENCODER_CH_R = ENCODER_RIGHT;

//--------------------------------------------------
//Configuration
//--------------------------------------------------
int encoderPPR_R = 70;
volatile const long debounce_time_R_HIGH = 200;
volatile const long debounce_time_R_LOW = 100;

//--------------------------------------------------
//Variable Declaration/Initialization
//--------------------------------------------------
volatile bool firstRead_R = true;
volatile unsigned long debounce_time_R = 0;

//only to debug interruption time
volatile unsigned long interr_curTime_us_R = 0;
volatile unsigned long interr_prevTime1_us_R = 0;
volatile unsigned long iinterr_prevTime2_us_R = 0;
volatile unsigned long interr_deltaTime_us_R = 0;
volatile unsigned long interr_highestTime_us_R = 0;

//Pulse Counter
volatile bool curA_R, prevA_R ;

bool debounce_treshold_R = false ;
volatile unsigned long pulseTime_R = 0;
volatile double encoderCount_R = 0;
volatile double encoderPulseCount_R=0;
volatile double encoderPulseError_R=0;
volatile bool encoderErro_R;

//Calculate Current Angle
double curAngle_R = 0;


//Calculate RPM
volatile unsigned long pulseTimeLatch_R = 0;
volatile unsigned long pulsePrevTime_R = 0;
volatile unsigned long pulsePrevPrevTime_R = 0;
volatile unsigned long pulseDeltaTime_R = 0;

volatile double encoderCountLatch_R = 0;
volatile double encoderPrevCount_R = 0;
volatile double encoderPrevPrevCount_R = 0;
volatile double encoderDeltaCount_R = 0;

volatile bool lastPulseForward_R = 0;
volatile bool lastPulseBackward_R = 0;

volatile double curRPM_R = 0;
volatile double prevRPM_R = 0;
volatile double highestRPM_R = 0;

volatile int filterGain_R = 20;
volatile double curRPM_Filtered_R = 0;


unsigned long lastDebounceTime = 0; 
unsigned long debounceDelay = 100; //[micro seconds]


//--------------------------------------------------
// Functions
//--------------------------------------------------

void IRAM_ATTR interruptionChR();



void EncoderR::setup()
{
    //Serial.println("EncSetup");
    
    //IO
    pinMode(DI_ENCODER_CH_R, INPUT_PULLUP);
    

    //Read Channels AB Initial State
    curA_R = digitalRead(DI_ENCODER_CH_R);
   
    prevA_R = curA_R;
    

    //Configure Interrupt
    attachInterrupt(digitalPinToInterrupt(DI_ENCODER_CH_R), interruptionChR, CHANGE);
   
    
}


void IRAM_ATTR EncoderR::interruptionChR()
{

    //Serial.println("A");
    //  interr_prevTime1_us_R = micros();

    pulseTime_R = micros();

    curA_R = digitalRead(DI_ENCODER_CH_R);

    // if(curA_R == prevA_R)
    // {
    //     //depois da interrupção, já leu e voltou ao valor anterior -> debounce = faz nada
    // }
    // else
    // {
    // prevA_R = curA_R;

    // if (curA_R == true)
    // {   
    //     encoderCount_R++;   
    // }
    // encoderPulseCount_R++;
    // }

    if (curA_R != prevA_R) {
        if ((micros() - lastDebounceTime) > debounceDelay) {
            prevA_R = curA_R ;
            encoderCount_R++;
            encoderPulseCount_R++;
        }
        lastDebounceTime = micros();
    }
}


double EncoderR::readAngle()
{
    curAngle_R = ((double)360.0 * (double)encoderCount_R) / (double)(encoderPPR_R);
    return curAngle_R;

}

double EncoderR::readTicks(){
    return encoderCount_R ;
}

double EncoderR::readRPM()
{

    noInterrupts(); //Disable interruptions - Critical code
    pulseTimeLatch_R = pulseTime_R;
    encoderCountLatch_R = encoderCount_R;
    interrupts(); //Re-Enable interruptions

    encoderDeltaCount_R = encoderCountLatch_R - encoderPrevCount_R;

    
    if (firstRead_R==true)
    {
        curRPM_R = 0;
        firstRead_R = false;
    }
    else
    {
        if (encoderDeltaCount_R != 0) //New pulses
        {
            
            pulseDeltaTime_R = pulseTimeLatch_R - pulsePrevTime_R;
            
            if (pulseDeltaTime_R < 1) //Prevent division by 0
            {
                curRPM_R = 0;
            }
            else
            {
                curRPM_R = (double)encoderDeltaCount_R*(1000000.0/(double)pulseDeltaTime_R)*60.0/128;
            }

            
            
        }
        else //No new pulses, use current time
        {
            pulseDeltaTime_R = micros() - pulsePrevTime_R;
         
            if (pulseDeltaTime_R < 1)
            {
                curRPM_R = 0;
            }
            else
            {
                curRPM_R = (double)1.0*(1000000.0/(double)pulseDeltaTime_R)*60.0/128.0;
            }

            

        }
    }
    
    
    encoderPrevPrevCount_R = encoderPrevCount_R;
    encoderPrevCount_R = encoderCountLatch_R;


    pulsePrevPrevTime_R = pulsePrevTime_R;
    if (encoderDeltaCount_R != 0) //New pulses to update time
    {
        pulsePrevTime_R = pulseTimeLatch_R;
    }
    

    if (curRPM_R < 0.5 && curRPM_R > -0.5)
    {
        curRPM_R = 0;
    }

    //filter glitches (position overflow)
    if ((curRPM_R > 10000) | (curRPM_R < -10000)){
        curRPM_R = prevRPM_R;
    }  else {
        prevRPM_R = curRPM_R;
    }
    
    //---
    curRPM_Filtered_R = (curRPM_Filtered_R*filterGain_R+curRPM_R)/(filterGain_R+1);
    if (curRPM_Filtered_R < 0.1 && curRPM_Filtered_R > -0.1)
    {
        curRPM_Filtered_R = 0;
    }
    

    //Store highest RPM ever
    if (curRPM_R > highestRPM_R){
        highestRPM_R = curRPM_R;
    }

    return curRPM_Filtered_R;

}


void EncoderR::reset()
{
  encoderCount_R = 0;
  encoderErro_R = false;
  highestRPM_R = 0;
  encoderPulseCount_R = 0;
  encoderPulseError_R = 0;
}


//--------------------------------------------------
//Debug Print
//--------------------------------------------------
void EncoderR:: debugPrint() {

    Serial.print("|Encoder->");

    Serial.print(digitalRead(DI_ENCODER_CH_R));
    //Serial.println(digitalRead(DI_ENCODER_CH_B));

    // Serial.print(", ErroCount");
    // Serial.print(encoderPulseError_R);

    //---

    Serial.print(":Pulsos");
    Serial.print(encoderCount_R);

    Serial.print(", curAngle_R:");
    Serial.print(curAngle_R);

    //---

    // Serial.print("P_T:");
    // Serial.print(pulseTimeLatch_R);

    // Serial.print(", P_PT:");
    // Serial.print(pulsePrevPrevTime_R);

    // Serial.print(", P_DT:");
    // Serial.print(pulseDeltaTime_R);

    // Serial.print(", P_C:");
    // Serial.print(encoderCountLatch_R);

    // Serial.print(", P_PC:");
    // Serial.print(encoderPrevPrevCount_R);
    
    // Serial.print(", P_DC:");
    // Serial.print(encoderDeltaCount_R);

    // Serial.print(", RPM:");
    // Serial.print(curRPM_R);

    Serial.print(", RPM_F:");
    Serial.print(curRPM_Filtered_R);
    
    // Serial.print(", RPM_H:");
    // Serial.print(highestRPM_R);
    

    Serial.println();

}