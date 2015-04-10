
const int ShiftPWM_latchPin=8;

const bool ShiftPWM_invertOutputs = false; 
const bool ShiftPWM_balanceLoad = false;

#include <ShiftPWM.h>   // include ShiftPWM.h after setting the pins!
#include "mpr121.h"
#include <Wire.h>


int led = 13;
int irqpin = 2;  // Digital 2
boolean touchStates[12]; //to keep track of the previous touch states

unsigned char maxBrightness = 255;
unsigned char pwmFrequency = 75;
int numRegisters = 2;
int numRGBleds = numRegisters*8/3;



//------------------------------------------ /////////////////////////////////////////          own variables

boolean fadedelay = false;
int senseValues[12];

long previousMillis[12];
boolean counterboolean = false;
long countermovement =0;

int fadeOutDelay = 10000;
int fadeInDelay = 100;

int ledCounter = 0;
int previouslednumber = 0;

long fadeOutDelayAfterMovement = 0;
long speedMesurement = 0;



unsigned long currentMillis = millis();

void setup(){
  Serial.begin(9600);

  pinMode(irqpin, INPUT);
  digitalWrite(irqpin, HIGH); //enable pullup resistor
  Wire.begin();
  pinMode(led, OUTPUT);   


  mpr121_setup();

  // Sets the number of 8-bit registers that are used.
  ShiftPWM.SetAmountOfRegisters(numRegisters);

  // SetPinGrouping allows flexibility in LED setup. 
  // If your LED's are connected like this: RRRRGGGGBBBBRRRRGGGGBBBB, use SetPinGrouping(4).
  ShiftPWM.SetPinGrouping(1); //This is the default, but I added here to demonstrate how to use the funtion

  ShiftPWM.Start(pwmFrequency,maxBrightness);

}



void loop()
{

 currentMillis = millis();

  if(counterboolean == true){
    countermovement ++;
  }

  //check all touch sensors 
  for (int i=0; i < 12; i++){
    if(touchStates[i] == 1){
      led0en1FadeIN(i);
    }
    if(touchStates[i] == 0 && senseValues[i] > 0 ){
      //senseValues[i]= fadeOutDelay;
      led0en1FadeOut(i);    
    }
  }
 
  readTouchInputs();  
  countNrOffLeds();
}
//---------------------------------------------------------------------------------------------------




















