/*
this file contains temperature sensor class 
member functions
1. constructor // initialise the lm35 pin
2. getTempCelcius() // returns float temp in celcius
3. getTempFahrenheit()// returns float temp in farhenheit
*/
#ifndef LM35_H
#define LM35_H
#include <Arduino.h>

static temp_pin;

class lm35{
 void lm35(int val)
    {
        temp_pin = val;
    }
float getTempCelcius()
{
int value = analogRead(temp_pin);
  float mv = ( val/1024.0)*5000;
  float cel = mv/10;
  float farh = (cel*9)/5 + 32;
  return(cel);
}
float getTempFahrenheit()
{
int value = analogRead(temp_pin);
  float mv = ( val/1024.0)*5000;
  float cel = mv/10;
  float farh = (cel*9)/5 + 32;
  return(farh);
}
};
#endif
