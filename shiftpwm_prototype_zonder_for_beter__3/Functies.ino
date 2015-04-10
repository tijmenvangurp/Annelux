
int countNrOffLeds(){
  ledCounter = 0;
  for (int i=0; i < 12; i++){
    if(senseValues[i]>10){
      ledCounter ++;
    }
  }
  return ledCounter;
}


void movementDetector(int count, int lednumber){
  //Serial.print("count = ");
//Serial.println(currentMillis - speedMesurement);
 int speedMovementHand = currentMillis - speedMesurement;
 

  if(count > 0 && count < 1000){
    //Serial.println(count);
    if ((previouslednumber - lednumber) > 0){

      Serial.println("Beweging naar links");

    }
    else if((previouslednumber - lednumber) < 0){
      Serial.println("Beweging naar Rechts");
      ledsAfterEachOther(count, lednumber,speedMovementHand);
    }
  }
  // previouslednumber - lednumber ( bijv 0 -1 of 8 - 9 < 0 is beweging naar rechts 9 - 8 = 1 beweging naar links > 0


  previouslednumber = lednumber;
  speedMesurement = currentMillis;
  //only add count if time betwee
}

void ledsAfterEachOther(int count, int lednumber, int speedMovementHand){
  int delayValue = map(count , 0, 1000,10,50);
  for (int i=lednumber; i < 12; i++){

    if(i > lednumber){
      ShiftPWM.SetOne(i-1,50);
    }
    if(i > (lednumber +1)){
      ShiftPWM.SetOne(i-2,15); 
    }
    ShiftPWM.SetOne(i,255);
    delay(40);
    ShiftPWM.SetAll(0);
  }
  for (int i=0; i < 12; i++){ 
    //resetting all the lights so that they are off
    senseValues[i] = 0;
  }
  ShiftPWM.SetAll(0);
  
  fadeOutDelayAfterMovement = currentMillis;
  
}

