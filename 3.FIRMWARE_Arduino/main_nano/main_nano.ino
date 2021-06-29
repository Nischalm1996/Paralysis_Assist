/*
*
*/

#include <Arduino.h>
#include "MainClass.h"

MainClass  ObjMenu;

void setup(void) {  
  //Serial.begin(9600);
  ObjMenu.Init();
}

void loop(void) {
ObjMenu.runMenu();
}
