#include "LPD8806.h"
#include "SPI.h"

// Example to control LPD8806-based RGB LED Modules in a strip

/*****************************************************************************/

// Number of RGB LEDs in strand:
int nLEDs = 96;
int red[96];
int green[96];
int blue[96];
int j = 0;


// Chose 2 pins for output; can be any valid output pins:
int dataPin  = 2;
int clockPin = 3;
int sensorPin = A0; 
int sensorPin2 = A1; 
int sensorValue = 0;
int sensorValue2 = 0;
int nrOfledsOn = 6;
float adcResult = 0;
float adcResult2 = 0;
int fadeoutX = 255;

boolean fadeout = false;
boolean fadeout2 = false;

LPD8806 strip = LPD8806(nLEDs, dataPin, clockPin);

long previousMillis = 0; 
long interval = 1000;   

void setup() {
  // Start up the LED strip
  strip.begin();
  Serial.begin(9600);



  // Update the strip, to start they are all 'off'
  strip.show();
}


void loop() {

  sensorValue2 = analogRead(sensorPin2);
  sensorValue = analogRead(sensorPin);
  // Serial.println(sensorValue);
  adcResult = adcResult * 0.95 + sensorValue * 0.05;
  adcResult2 = adcResult2 * 0.95 + sensorValue2 * 0.05;


  // int sensorValueMapped = map(sensorValue,0,1023,0,48);

  // strip.show(); 

  if (adcResult <520){
    if (j < 255){
      j++;
    }
    for(int i = 9;i<18; i++){
      red[i] = 255;
      green[i] = 255;
      blue[i] = 0;
      strip.setPixelColor(i,j,j,0);

    }
    for(int i = 22;i<31; i++){
      red[i] = 255;
      green[i] = 255;
      blue[i] = 0;
      strip.setPixelColor(i,j,j,0);

    }
    strip.show();
    fadeout = true; 
    fadeoutX = 255;
  }
  else if(adcResult2 <300){
    for(int i = 0;i<9; i++){
      red[i] = 255;
      green[i] = 255;
      blue[i] = 0;
      strip.setPixelColor(i,255,0,0);
    }

    for(int i = 31;i<40; i++){
      red[i] = 255;
      green[i] = 255;
      blue[i] = 0;
      strip.setPixelColor(i,0,0,255);
    }
    strip.show(); 
    fadeoutX = 255;

  }
  else{

    unsigned long currentMillis = millis();
    if(currentMillis - previousMillis > interval) {
      //for(int i=0; i<strip.numPixels(); i++) strip.setPixelColor(i, 0);

      if(j == 0){
        fadeout = false;
      }
      previousMillis = currentMillis; 
      j = 0 ; 
    }
    if (fadeout = true && fadeoutX > 0 ){
      fadeoutX --;

      for(int i=9; i<18; i++) {
        strip.setPixelColor(i, fadeoutX,fadeoutX,0);
      }
      for(int i=22; i<31; i++) {
        strip.setPixelColor(i, fadeoutX,fadeoutX,0);
      }      
    }
    strip.show();

  }


  Serial.println(fadeoutX);



}


























