/* LM393.h
 *  This file proviodes interface with sound sensor
 */
#ifndef LM393_H
#define LM393_H

 class LM393
 {
  public :
  byte soundPin = 0;
  LM393(byte soundSenPin)
  {
    soundPin = soundSenPin;
  }

  ~LM393()
  {
    
  }

  void Init()
  {
    pinMode(soundPin, INPUT);
  }

  /* Digital out signal read from sound sensor */
  /* returns True when sound detected */
  bool readSoundSens()
  {
    //Sensor Provides LOW when sound detected
   return !digitalRead(soundPin); 
  }
  
 };

#endif
