void checkArea(){
  boolean foundArea = false;
  //---------------------------------------------------------------------------------------------0 = middenblok
  if(!foundArea){
    for(int i = 6; i < (numberOfLeds - 2) ; i = i+4){
      if (previousLed == i){
        blinkLed(0,i);
        foundArea = true;
        break;
      }
    }
    if(!foundArea){
      for(int i = 5; i < (numberOfLeds - 3) ; i = i+4){
        if (previousLed == i){
          blinkLed(0,i);
          foundArea = true;
          break;
        }
      }
    }
  }
  //--------------------------------------------------------------------------------------------- 1= links
  if(!foundArea){
    for(int i = 7; i < (numberOfLeds - 1) ; i = i+4){
      if (previousLed == i){
        blinkLed(1,i);
        foundArea = true;
        break;
      }
    }
  }
  //--------------------------------------------------------------------------------------------- 2 = rechts
  if(!foundArea){
    for(int i = 4; i < (numberOfLeds - verticalCollums) ; i = i+4){
      if (previousLed == i){
        blinkLed(2,i);
        foundArea = true;
        break;
      }
    }
  }
  //--------------------------------------------------------------------------------------------- 3 = boven
  if(!foundArea){ 
    for(int i = 1 ; i < (verticalCollums -1); i++ ){
      if (previousLed == i){
        blinkLed(3,i);
        foundArea = true;
        break;
      }
    }
  }
  //--------------------------------------------------------------------------------------------- 4 = onder
  if(!foundArea){
    for(int i = ((numberOfLeds +1) - verticalCollums) ; i < numberOfLeds -1; i++ ){
      //Serial.println(i);
      if (previousLed == i){
        blinkLed(4,i);
        foundArea = true;
        break;
      }
    }
  }
  //---------------------------------------------------------------------------------------------  5 = Rechtsboven 
  if(!foundArea){
    if(previousLed == 0 ){
      blinkLed(5,0);
      foundArea = true;
    }
  }
  //---------------------------------------------------------------------------------------------  6 = links Onder
  if(!foundArea){
    if( previousLed == (numberOfLeds-1)){
      blinkLed(6,numberOfLeds-1);
      foundArea = true;
    }
  }
  //--------------------------------------------------------------------------------------------- 7 = Linkgsboven 
  if(!foundArea){
    if( previousLed == (verticalCollums-1)  ){
      blinkLed(7,verticalCollums-1);
      foundArea = true;
    }
  }
  //---------------------------------------------------------------------------------------------  8 = rechtsOnder
  if(!foundArea){
    if(previousLed == (numberOfLeds-verticalCollums) ){
      blinkLed(8,numberOfLeds-verticalCollums);
      foundArea = true;
    }
  }
}


void blinkLed(int area, int prevLed){


  ShiftPWM.SetAll(0);
  int ledToBlink;
  switch (area) {
  case 0:   
    // 0 = middenblok
    ledToBlink = prevLed -( middenBlok[random(3)]);
    while(ledToBlink == checkTwice){
      ledToBlink = prevLed -( middenBlok[random(3)]);
    }
    break;
  case 1:    
    // 1 = links
    ledToBlink =  prevLed - ((naast[random(2)])*-1);
    while(ledToBlink == checkTwice){
      ledToBlink =  prevLed - ((naast[random(2)])*-1);
    }
    break;
  case 2:    
    // 2 = rechts
    ledToBlink = prevLed - (naast[random(2)]);
    while(ledToBlink == checkTwice){
      ledToBlink = prevLed - (naast[random(2)]);
    }
    break;
  case 3:    
    // 3 = boven
    ledToBlink = prevLed - ( boven[random(2)]);
    while(ledToBlink == checkTwice){
      ledToBlink = prevLed - ( boven[random(2)]);
    }
    break;
  case 4:    
    // 4 = onder
    ledToBlink = prevLed - ((boven[random(2)])*-1);
    while(ledToBlink == checkTwice){
      ledToBlink = prevLed - ((boven[random(2)])*-1);
    }
    break;
  case 5:    
    // 5 = rechtsboven
    ledToBlink = prevLed - ((hoek2[random(1)])*-1);
    while(ledToBlink == checkTwice){
      ledToBlink = prevLed - ((hoek2[random(1)])*-1);
    }
    break;
  case 6:    
    // 6 = linksonder
    ledToBlink = prevLed - ((hoek2[random(1)]));
    while(ledToBlink == checkTwice){
      ledToBlink = prevLed - ((hoek2[random(1)]));
    }
    break;
  case 7:    
    // 7 = linksboven
    ledToBlink = prevLed - ((hoek[random(1)])*-1);
    while(ledToBlink == checkTwice){
      ledToBlink = prevLed - ((hoek[random(1)])*-1);
    }
    break;
  case 8:    
    // 8 = rechtsonder
    ledToBlink = prevLed - (hoek[random(1)]);
    while(ledToBlink == checkTwice){
      ledToBlink = prevLed - (hoek[random(1)]);
    }
    break;
  } 
  //Serial.println(checkTwice);
  // Serial.println(ledToBlink);
  ShiftPWM.SetOne(ledToBlink,255);
  ShiftPWM.SetOne(checkTwice,255);
  // Serial.println(ledToBlink);
  checkTwice =  prevLed;
  previousLed = ledToBlink;
  //Serial.println("functie gestart");
  // int delayValue = random(20,250); // Some random shit going on her <--
  int delayValue = abs(map(getMeasurement_sensor_one(),100,260,30,200));
  Serial.print(" sensor  ");
  Serial.println(getMeasurement_sensor_one());
  Serial.print(" delay  ");
  Serial.println(delayValue);
  delay(delayValue);
}





