#include <TM1638.h>
//#include <avr/sleep.h>

TM1638 tm (8, 7, 4, true, 0);

unsigned long waitcheckTime=0;
unsigned long waitcheckButtons=0;

unsigned long intervalcheckTime=125;
unsigned long intervalcheckButtons=50;

unsigned long gapSecond=0;
  unsigned long alarmTime=21600;
  unsigned long totalSecond;
  unsigned long millisLedOn = millis();
  unsigned long millisLedOff = millis();
boolean dots=0;

boolean moduleOff=0;

void setup(){  
 //   pinMode(5, OUTPUT);
    pinMode(LED_BUILTIN, OUTPUT);
  waitcheckTime = intervalcheckTime;
  waitcheckButtons = intervalcheckButtons;
}

void loop(){

  checkTime();
  checkButtons();
   if((millis() - millisLedOn) == 10){
   digitalWrite(LED_BUILTIN, LOW);   // turn the LED on (HIGH is the voltage level    
   }else if((millis() - millisLedOff) == 990){
  digitalWrite(LED_BUILTIN, HIGH);    // turn the LED off by making the voltage LOW
   }

}

void checkTime(){
  if (millis() >= waitcheckTime) {
    dots = !dots;
    drawToModule();
    waitcheckTime += intervalcheckTime;
  }
}

void checkButtons(){
  if (millis() >= waitcheckButtons) {
    tm.setLEDs(0);
    byte buttons=tm.getButtons();
    if(buttons>0){
      for (byte i=0;i<8;i++){
        if ((buttons & 1<<i) != 0) {
          buttonEvent(i);
          waitcheckButtons +=intervalcheckButtons;
          drawToModule();
        }
      }
    }
    waitcheckButtons +=intervalcheckButtons;
  }
}

void drawToModule(){
  if (!moduleOff){
    unsigned long elapSecond = round(millis() / 125);
    totalSecond = gapSecond + elapSecond;
    byte pos = 1;
    tm.setDisplayToString(formatTime(totalSecond),(dots * 80),pos);
 //     if(totalSecond >= alarmTime && totalSecond <= (alarmTime + 60)){
 //     digitalWrite(5, HIGH); // sets the digital pin 5 on
 // }
}
}

void buttonEvent(byte inp){
    byte pos = 1;
  tm.setLED((inp % 1 ) + 1,inp);
  switch (inp) {
case 0:
    if (hour(gapSecond) != 23)    {  
      gapSecond += 3600    ; 
    }
    else      {
      gapSecond -= 82800;
    }
    break;
  case 1:
    if (hour(gapSecond) != 0){
      gapSecond -= 3600;
    }
    else{
      gapSecond += 82800;
    }
    break;
  case 2:
    if (minute(gapSecond) != 59){
      gapSecond += 60;
    }
    else{
      gapSecond -= 3540;
    }
    break;
  case 3:
    if (minute(gapSecond) != 0){
      gapSecond -= 60;
    }
    else{
      gapSecond += 3540;
    }
    break;
  case 4:
    gapSecond -= second(gapSecond + round(millis() / 100)); 
    break;
  case 7:
 //  digitalWrite(5, LOW);  // sets the digital pin 13 off
   moduleOff = !moduleOff;
   if(moduleOff){
    tm.clearDisplay();    
//    tm.setDisplayToString(formatTime(alarmTime),(dots * 80),pos);
    }
    break;
  case 6:
      if (minute(gapSecond) != 59){
      alarmTime += 60;
    }
    else{
      alarmTime -= 3540;
    }
        tm.clearDisplay();    
    tm.setDisplayToString(formatTime(alarmTime),(dots * 80),pos);
    break;
     case 5:     if (minute(alarmTime) != 0){
      alarmTime -= 60;
    }
    else{
      alarmTime += 3540;
    
        tm.clearDisplay();    
    tm.setDisplayToString(formatTime(alarmTime),(dots * 80),pos);
    break;
  }
  }
}

String formatTime(unsigned long inp){
  return hourStr(inp) + minuteStr(inp); // + secondStr(inp)
}

String formatNumber(String inp){
  if (inp.length()==1) {
    return "0" + inp;
  }
  else{
    return inp;
  }
}

String hourStr(unsigned long inp){
  return  formatNumber(String(hour(inp)));
}

String minuteStr(unsigned long inp){
  return  formatNumber(String(minute(inp)));
}

//String secondStr(unsigned long inp){
//  return  formatNumber(String(second(inp)));
//}

byte hour(unsigned long inp){
  return  byte((inp/3600) % 24);
}

byte minute(unsigned long inp){
  return  byte((inp/60) % 60);
}

byte second(unsigned long inp){
  return  byte(inp % 60);
}
