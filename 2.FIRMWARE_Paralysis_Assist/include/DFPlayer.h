#ifndef DFPLAYER_H
#define DFPLAYER_H

#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

/*
  Command LIST:
  1.
  2.
  3.
  4.
  5.
  6.
  7.
  8.
  9.
*/
SoftwareSerial mySoftwareSerial(10, 11); // RX, TX
DFRobotDFPlayerMini myDFPlayer;

Class DFPlayer
{
public:
  void begin()
  {
    mySoftwareSerial.begin(9600);
    Serial.begin(115200);


    While(!myDFPlayer.begin(mySoftwareSerial)) {  //Use softwareSerial to communicate with mp3.
    }
    Serial.println(F("DFPlayer Mini online."));

    myDFPlayer.volume(10);  //Set volume value. From 0 to 30
    myDFPlayer.play(1);  //Play the first mp3
  }
  void DFPlay(byte number)
  {
    myDFPlayer.play(number);
  }
}


#endif //DFPLAYER_H
