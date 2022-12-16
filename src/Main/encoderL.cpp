
 #include "encoderL.h" // header in local directory
 #include "config.h"
//--------------------------------------------------
//Pinout
//--------------------------------------------------
volatile int DI_ENCODER_CH_A = ENCODER_LEFT;


//--------------------------------------------------
//Configuration
//--------------------------------------------------
int encoderPPR = 70;
volatile const long DEBOUNCE_TIME_HIGH = 200;
volatile const long DEBOUNCE_TIME_LOW = 100;

//--------------------------------------------------
//Variable Declaration/Initialization
//--------------------------------------------------
volatile bool firstRead = true;
volatile unsigned long debounce_time = 0;

//only to debug interruption time
volatile unsigned long interr_curTime_us = 0;
volatile unsigned long interr_prevTime1_us = 0;
volatile unsigned long interr_prevTime2_us = 0;
volatile unsigned long interr_deltaTime_us = 0;
volatile unsigned long interr_highestTime_us = 0;

//Pulse Counter
volatile bool curA, prevA ;

bool debounce_treshold = false ;
volatile unsigned long pulseTime = 0;
volatile double encoderCount = 0;
volatile double encoderPulseCount=0;
volatile double encoderPulseError=0;
volatile bool encoderErro;

//Calculate Current Angle
double curAngle = 0;


//Calculate RPM
volatile unsigned long pulseTimeLatch = 0;
volatile unsigned long pulsePrevTime = 0;
volatile unsigned long pulsePrevPrevTime = 0;
volatile unsigned long pulseDeltaTime = 0;

volatile double encoderCountLatch = 0;
volatile double encoderPrevCount = 0;
volatile double encoderPrevPrevCount = 0;
volatile double encoderDeltaCount = 0;

volatile bool lastPulseForward = 0;
volatile bool lastPulseBackward = 0;

volatile double curRPM = 0;
volatile double prevRPM = 0;
volatile double highestRPM = 0;

volatile int filterGain = 20;
volatile double curRPM_Filtered = 0;

unsigned long lastDebounceTime = 0; 
unsigned long debounceDelay = 100; //[micro seconds]

//--------------------------------------------------
// Functions
//--------------------------------------------------

void IRAM_ATTR interruptionChL();



void EncoderL::setup()
{
    //Serial.println("EncSetup");
    
    //IO
    pinMode(DI_ENCODER_CH_A, INPUT_PULLUP);
    

    //Read Channels AB Initial State
    curA = digitalRead(DI_ENCODER_CH_A);
   
    prevA = curA;
    

    //Configure Interrupt
    attachInterrupt(digitalPinToInterrupt(DI_ENCODER_CH_A), interruptionChL, CHANGE);
   
    
}


void IRAM_ATTR EncoderL::interruptionChL()
{

    //Serial.println("A");
    //  interr_prevTime1_us = micros();

    pulseTime = micros();

    curA = digitalRead(DI_ENCODER_CH_A);

    // if(curA == prevA)
    // {
    //     //depois da interrupção, já leu e voltou ao valor anterior -> debounce = faz nada
    // }
    // else
    // {
    // prevA = curA;

    // if (curA == true)
    // {   
    //     encoderCount++;   
    // }
    // encoderPulseCount++;
    // }

    if (curA != prevA) {
        if ((micros() - lastDebounceTime) > debounceDelay) {
            prevA = curA ;
            encoderCount++;
            encoderPulseCount++;
        }
        lastDebounceTime = micros();
    }
}

double EncoderL::readTicks(){
    return encoderCount ;
}

double EncoderL::readAngle()
{
    curAngle = ((double)360.0 * (double)encoderCount) / (double)(encoderPPR);
    return curAngle;

}


double EncoderL::readRPM()
{

    noInterrupts(); //Disable interruptions - Critical code
    pulseTimeLatch = pulseTime;
    encoderCountLatch = encoderCount;
    interrupts(); //Re-Enable interruptions

    encoderDeltaCount = encoderCountLatch - encoderPrevCount;

    
    if (firstRead==true)
    {
        curRPM = 0;
        firstRead = false;
    }
    else
    {
        if (encoderDeltaCount != 0) //New pulses
        {
            
            pulseDeltaTime = pulseTimeLatch - pulsePrevTime;
            
            if (pulseDeltaTime < 1) //Prevent division by 0
            {
                curRPM = 0;
            }
            else
            {
                curRPM = (double)encoderDeltaCount*(1000000.0/(double)pulseDeltaTime)*60.0/128.0;
            }

            
            
        }
        else //No new pulses, use current time
        {
            pulseDeltaTime = micros() - pulsePrevTime;
         
            if (pulseDeltaTime < 1)
            {
                curRPM = 0;
            }
            else
            {
                curRPM = (double)1.0*(1000000.0/(double)pulseDeltaTime)*60.0/128.0;
            }

            

        }
    }
    
    
    encoderPrevPrevCount = encoderPrevCount;
    encoderPrevCount = encoderCountLatch;


    pulsePrevPrevTime = pulsePrevTime;
    if (encoderDeltaCount != 0) //New pulses to update time
    {
        pulsePrevTime = pulseTimeLatch;
    }
    

    if (curRPM < 0.5 && curRPM > -0.5)
    {
        curRPM = 0;
    }

    //filter glitches (position overflow)
    if ((curRPM > 10000) | (curRPM < -10000)){
        curRPM = prevRPM;
    }  else {
        prevRPM = curRPM;
    }
    
    //---
    curRPM_Filtered = (curRPM_Filtered*filterGain+curRPM)/(filterGain+1);
    if (curRPM_Filtered < 0.1 && curRPM_Filtered > -0.1)
    {
        curRPM_Filtered = 0;
    }
    

    //Store highest RPM ever
    if (curRPM > highestRPM){
        highestRPM = curRPM;
    }

    return curRPM_Filtered;

}

void EncoderL::reset()
{
  encoderCount = 0;
  encoderErro = false;
  highestRPM = 0;
  encoderPulseCount = 0;
  encoderPulseError = 0;
}


//--------------------------------------------------
//Debug Print
//--------------------------------------------------
void EncoderL:: debugPrint() {

    Serial.print("|Encoder->");

    Serial.print(digitalRead(DI_ENCODER_CH_A));
    //Serial.println(digitalRead(DI_ENCODER_CH_B));

    // Serial.print(", ErroCount");
    // Serial.print(encoderPulseError);

    //---

    Serial.print(":Pulsos");
    Serial.print(encoderCount);

    Serial.print(", CurAngle:");
    Serial.print(curAngle);

    //---

    // Serial.print("P_T:");
    // Serial.print(pulseTimeLatch);

    // Serial.print(", P_PT:");
    // Serial.print(pulsePrevPrevTime);

    // Serial.print(", P_DT:");
    // Serial.print(pulseDeltaTime);

    // Serial.print(", P_C:");
    // Serial.print(encoderCountLatch);

    // Serial.print(", P_PC:");
    // Serial.print(encoderPrevPrevCount);
    
    // Serial.print(", P_DC:");
    // Serial.print(encoderDeltaCount);

    // Serial.print(", RPM:");
    // Serial.print(curRPM);

    Serial.print(", RPM_F:");
    Serial.print(curRPM_Filtered);
    
    // Serial.print(", RPM_H:");
    // Serial.print(highestRPM);
    

    Serial.println();

}