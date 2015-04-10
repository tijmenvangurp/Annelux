/************************************************************************************************************************************
 * ShiftPWM blocking RGB fades example, (c) Elco Jacobs, updated August 2012.
 *
 * ShiftPWM blocking RGB fades example. This example uses simple delay loops to create fades.
 * If you want to change the fading mode based on inputs (sensors, buttons, serial), use the non-blocking example as a starting point.
 * Please go to www.elcojacobs.com/shiftpwm for documentation, fuction reference and schematics.
 * If you want to use ShiftPWM with LED strips or high power LED's, visit the shop for boards.
 ************************************************************************************************************************************/

//#include <Servo.h> <-- If you include Servo.h, which uses timer1, ShiftPWM will automatically switch to timer2

// Clock and data pins are pins from the hardware SPI, you cannot choose them yourself if you use the hardware SPI.
// Data pin is MOSI (Uno and earlier: 11, Leonardo: ICSP 4, Mega: 51, Teensy 2.0: 2, Teensy 2.0++: 22) 
// Clock pin is SCK (Uno and earlier: 13, Leonardo: ICSP 3, Mega: 52, Teensy 2.0: 1, Teensy 2.0++: 21)

// You can choose the latch pin yourself.
const int ShiftPWM_latchPin=8;

// ** uncomment this part to NOT use the SPI port and change the pin numbers. This is 2.5x slower **
// #define SHIFTPWM_NOSPI
// const int ShiftPWM_dataPin = 11;
// const int ShiftPWM_clockPin = 13;


// If your LED's turn on if the pin is low, set this to true, otherwise set it to false.
const bool ShiftPWM_invertOutputs = false; 

// You can enable the option below to shift the PWM phase of each shift register by 8 compared to the previous.
// This will slightly increase the interrupt load, but will prevent all PWM signals from becoming high at the same time.
// This will be a bit easier on your power supply, because the current peaks are distributed.
const bool ShiftPWM_balanceLoad = false;

#include <ShiftPWM.h>   // include ShiftPWM.h after setting the pins!
#include "URMSerial.h"

// Here you set the number of brightness levels, the update frequency and the number of shift registers.
// These values affect the load of ShiftPWM.
// Choose them wisely and use the PrintInterruptLoad() function to verify your load.
// There is a calculator on my website to estimate the load.

unsigned char maxBrightness = 255;
unsigned char pwmFrequency = 75;
int numRegisters = 3;
int numRGBleds = numRegisters*8/3;

int middenBlok[] = {
  -4,-1,1,4,};

int boven[] ={
  -1,-4,1};

int naast[] = {
  4,-1,-4};

int hoek[] = {
  -1,4};

int hoek2[] = {
  1,4};

int previousLed = 5;

int numberOfLeds = 24;
int verticalCollums = 4;
int horizontalCollums = numberOfLeds / horizontalCollums;
int checkTwice;

int arduinoSensorOne_Value = 0;

//3	2	1	0
//7	6	5	4
//11	10	9	8
//15	14	13	12
//19	18	17	16
//23	22	21	20

//int delayValue = random(20,250);

//-------------------------------------------------------------------------------------- DISTANCE VARIABLES

// # Connection:
// #       VCC (Arduino)   -> Pin 1 VCC (URM37 V3.2)
// #       GND (Arduino)   -> Pin 2 GND (URM37 V3.2)
// #       Pin 6 (Arduino) -> Pin 9 TXD (URM37 V3.2)
// #       Pin 7 (Arduino) -> Pin 8 RXD (URM37 V3.2)
// #

// The measurement we're taking
#define DISTANCE 1
#define TEMPERATURE 2
#define ERROR 3
#define NOTREADY 4
#define TIMEOUT 5

URMSerial urm;


int outputValue;

void setup(){
  Serial.begin(9600);
  // Sets the number of 8-bit registers that are used.
  ShiftPWM.SetAmountOfRegisters(numRegisters);
  // SetPinGrouping allows flexibility in LED setup. 
  // If your LED's are connected like this: RRRRGGGGBBBBRRRRGGGGBBBB, use SetPinGrouping(4).
  ShiftPWM.SetPinGrouping(1); //This is the default, but I added here to demonstrate how to use the funtion
  ShiftPWM.Start(pwmFrequency,maxBrightness);
  
  //-------------------------------------------------------------------------------------- DISTANCE
  urm.begin(6,7,9600);  // RX Pin, TX Pin, Baud Rate
  Serial.println("URM37 Library by Miles Burton");
}

void loop()
{    
  // Turn all LED's off.
  ShiftPWM.SetAll(0);
  checkArea();
  //Serial.print("one = ");
  //Serial.println(getMeasurement_sensor_one());
}



















