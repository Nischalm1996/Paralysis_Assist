
/* This file contains function and definitions for Tempaature sensor LM35 
 * 
 * Board connection configuration, A3 = analog Pin to read temparature
 */
#ifndef LM35_H
#define LM35_H

#include "Arduino.h"

class lm35
{
  public:
  byte temp_pin =0; 
  
  lm35(byte val)
  {
    // constructore
    temp_pin = val;
  }
  
  /* Get temparature in Celcius */ 
  float getTempCelcius()
  {
   //Serial.println((((analogRead(temp_pin) * (500* 1.0 / 1024.0))/10));
    return (float)(((analogRead(temp_pin) * (5000* 1.0 / 1024.0))/10) - 7);
    //return cel;
  }
  
  /* Get the temparature in Fahrenheit */
  float getTempFahrenheit()
  {
    return (float)((getTempCelcius() *9)/5 + 32);
    
    //return fahrenH;
  }
  
};

#endif
