#include <Arduino.h>
#include "SD_Speaker.h"

sdSpeaker speakObj;
void setup()
{
  // put your setup code here, to run once:
  speakObj.Init(SD_ChipSelectPin, SpeakerPin);
  speakObj.play_music(1);
}

void loop() {
  // put your main code here, to run repeatedly:
  //demonstating changes in github
}