#include <Arduino.h>
#include "MainClass.h"

MainClass mainObj;
void setup()
{
 mainObj.Init();
}

void loop()
{
  mainObj.runMenu();

}