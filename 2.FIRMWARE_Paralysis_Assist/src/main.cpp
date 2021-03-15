#include <Arduino.h>
#include "lm35.h"
void setup() {
  // put your setup code here, to run once:
  lm35 temp(1);
  lm35 temp_2(2);
  }

void loop() {
  // put your main code here, to run repeatedly:
  //demonstating changes in github
  float a = temp.getTempCelcius();
}