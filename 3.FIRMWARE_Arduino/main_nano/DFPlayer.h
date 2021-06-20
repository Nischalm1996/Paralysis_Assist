#ifndef DFPLAYER_H
#define DFPLAYER_H

#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

/*
  Command LIST:
  1.Medicine
  2.need help i fell down
  3.fan
  4.food
  5.water
  6.light
  7.messenger
  8.nurse
  9.thank you
*/
SoftwareSerial mySoftwareSerial(3, 2); // RX, TX
DFRobotDFPlayerMini myDFPlayer;

class DFPlayer
{
  public:
    void begin()
    {
      mySoftwareSerial.begin(9600);
    }
    void beginSetup()
    {
      mySoftwareSerial.begin(9600);
      //Serial.begin(115200);
      while (!myDFPlayer.begin(mySoftwareSerial))
      { //Use softwareSerial to communicate with mp3.
      }
      //Serial.println(F("DFPlayer Mini online."));
      myDFPlayer.volume(30); //Set volume value. From 0 to 30
      // myDFPlayer.play(1);    //Play the first mp3
    }
    void DFPlay(byte number)
    {
      myDFPlayer.play(number);
    }
};

#endif //DFPLAYER_H
