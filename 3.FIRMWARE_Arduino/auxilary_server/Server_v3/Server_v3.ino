#include <SoftwareSerial.h>

SoftwareSerial SoftSerial(D8, D7);
boolean fall = false;
boolean light1 = false;
boolean light2 = false;
boolean light3 = false;
void setup()
{
  Serial.begin(115200);
  Serial.println("Begin");
  SoftSerial.begin(9600);
}
String dataIn = "";
char c = 0;
void loop()
{
  while (SoftSerial.available() > 0)
  {
    c = SoftSerial.read();
    Serial.println(c);
    if (c == 'X') {
      break;
    }
    else    {
      dataIn = dataIn + c;
    }
    //Serial.println(c);

  }
  //Serial.println(dataIn);
  if (c == 'X')
  {
    parse_the_data();
  }
  c = 0;
  dataIn = "";
}
void parse_the_data()
{
  int indexofS = dataIn.indexOf("*");
  int indexofx = dataIn.indexOf("X");

  String dat = dataIn.substring (indexofS + 1 , indexofx);

  if (dat == "1")
  {
    light1 = !light1;
  }
  if (dat == "2")
  {
    light2 = !light2;
  }
  if (dat == "3")
  {
    light3 = !light3;
  }
  if (dat == "4")
  {
    fall = true;
    //send data to client
  }
  fall = false;
}
