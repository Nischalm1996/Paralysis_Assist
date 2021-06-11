#include <Arduino.h>
#include "led.h"
#include "DFPlayer.h"
LEDClass ledobj;
DFPlayer playobj;

void setup()
{
  // put your setup code here, to run once:
  ledobj.beginled();
  ledobj.demoLed();
  playobj.begin();
}

void loop()
{
  // put your main code here, to run repeatedly:
  //demonstating changes in github
  int i;
  for (i = 1; i < 10; i++)
  {
    ledobj.setColor(0, 0, 255);
    playobj.DFPlay(i);
    delay(3000);
    ledobj.setColor(0, 0, 0);
    delay(500);
    ledobj.setColor(0, 255, 0);
    delay(300);
    ledobj.setColor(0, 0, 0);
  }
}