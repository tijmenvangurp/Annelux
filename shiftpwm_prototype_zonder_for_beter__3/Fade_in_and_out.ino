void led0en1FadeIN(int lednumber){
  //  Serial.print("led value from led nr ");
  //  Serial.print(lednumber);
  //  Serial.print(" = ");
  //  Serial.println(senseValues[lednumber]);
  if(counterboolean == true){
    countermovement ++;
  }

  long brightness = map(senseValues[lednumber],0,(fadeInDelay +3),0,255);

  if (brightness > 255){
    senseValues[lednumber] = 255;
  }
  ShiftPWM.SetOne(lednumber,brightness);
  ShiftPWM.SetOne(lednumber+1,brightness);
  senseValues[lednumber] ++;
}


void led0en1FadeOut(int lednumber){
  //Serial.println(senseValues[lednumber]);
  if(counterboolean == true){
    countermovement ++;
  }

  long brightness = map(senseValues[lednumber],0,fadeOutDelay,0,255);
  if (brightness < 4){
    senseValues[lednumber] = 0;
    brightness = 0;

  }
    ShiftPWM.SetOne(lednumber,brightness);
    ShiftPWM.SetOne(lednumber+1,brightness);
    senseValues[lednumber] = (senseValues[lednumber] - ledCounter); 
  
}



