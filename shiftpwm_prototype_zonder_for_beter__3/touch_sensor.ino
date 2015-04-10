void readTouchInputs(){

  if(counterboolean == true){
    countermovement ++;
  }
  if(!checkInterrupt()){

    //read the touch state from the MPR121
    Wire.requestFrom(0x5A,2); 

    byte LSB = Wire.read();
    byte MSB = Wire.read();

    uint16_t touched = ((MSB << 8) | LSB); //16bits that make up the touch states


    for (int i=0; i < 12; i++){  // Check what electrodes were pressed
      if(touched & (1<<i)){

        if(touchStates[i] == 0){
          digitalWrite(led, HIGH);
          //pin i was just touched
          //          Serial.print("pin ");
          //          Serial.print(i);
          //          Serial.println(" was just touched");
          //led0en1FadeIN(i);
          counterboolean = false;
          movementDetector(countermovement, i);
          countermovement = 0;
          touchStates[i] = 1;

          if(counterboolean == true){
            countermovement ++;
          }
        }
        else if(touchStates[i] == 1){
          //          Serial.print(i);
          //          Serial.println("still touching");
          //pin i is still being touched
        }  


      } 
      else{
        if(touchStates[i] == 1){
          //          Serial.print("pin ");
          //          Serial.print(i);
          digitalWrite(led, LOW);
          //          Serial.println(" is no longer being touched");
          //Serial.println(currentMillis);
          if (currentMillis - fadeOutDelayAfterMovement > 1000){
          senseValues[i] = fadeOutDelay;
          }
               
          
          // led0en1FadeOut(i);
          counterboolean = true;
          
          
          if(counterboolean == true){
            countermovement ++;
          }


          //pin i is no longer being touched
        }

        touchStates[i] = 0;
      }

    }

  }
}



