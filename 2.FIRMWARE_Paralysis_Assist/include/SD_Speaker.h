#ifndef SD_SPEAKER_H
#define SD_SPEAKER_H

/*
   This module is for playing SD card audio through speaker
*/
#include "SD.h"
#include "TMRpcm.h"
//#include "SPI.h"

byte SD_ChipSelectPin = 2; // = 2; //current CS configuration
byte SpeakerPin = 9;       // = 4;cahanged to 3  // speaker pin
TMRpcm tmrpcm;

class sdSpeaker
{
public:
  void Init(byte SD_Card_CS_Pin, byte Speaker_Pin)
  {
    SD_ChipSelectPin = SD_Card_CS_Pin;
    SpeakerPin = Speaker_Pin;

    tmrpcm.speakerPin = SpeakerPin;
    Serial.begin(9600);
    if (!SD.begin(SD_ChipSelectPin))
    {
      Serial.println(F("SD fail"));
      return;
    }
    Serial.println(F("SD ok"));
    tmrpcm.setVolume(6);
  }

  void play_music(byte num)
  {
    if (num == 1)
    {
      tmrpcm.play("tqs.wav");
    }
    else if (num == 2)
    {
      tmrpcm.play("mess.wav");
    }
    else if (num == 3)
    {
      tmrpcm.play("nurs.wav");
    }
    else if (num == 4)
    {
      tmrpcm.play("h20.wav");
    }
    else if (num == 5)
    {
      tmrpcm.play("fall.wav");
    }
    else if (num == 6)
    {
      tmrpcm.play("drug.wav");
    }
    else if (num == 7)
    {
      tmrpcm.play("light.wav");
    }
    else if (num == 8)
    {
      tmrpcm.play("food.wav");
    }
    else if (num == 9)
    {
      tmrpcm.play("fan.wav");
    }
    else
    {
      // do nothing
    }
  }
  void play_all()
  {
    byte i = 0;
    for (i = 0; i <= 9; i++)
    {
      play_music(i);
      delay(5000);
    }
  }
};

#endif