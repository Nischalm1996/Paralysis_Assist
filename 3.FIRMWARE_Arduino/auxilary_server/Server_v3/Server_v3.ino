
boolean fall = false;
boolean light1 = false;
boolean light2 = false;
boolean light3 = false;
void setup()
{
  Serial.begin(9600);
  //Serial.println("Begin");
  //Serial.println("working");
}
String dataIn = "";
char c = 0;
void loop()
{
  while (Serial.available() > 0)
  {
    c = Serial.read();
    if (c == 'X') {
      //dataIn = dataIn + c;
      break;
    }
    else if (c != '\n')   {
      dataIn = dataIn + c;
    }
   // Serial.print("dataIn:"); Serial.println(dataIn);

  }
  if (c == 'X')
  {
    //Serial.println("parse");
    //Serial.println(dataIn);
    parse_the_data();
  }

}
void parse_the_data()
{
  int indexofS = dataIn.indexOf("*");
  int indexofx = dataIn.indexOf("X");

  String dat = dataIn.substring (indexofS +1 , indexofx);
  //Serial.print("Dat:"); Serial.println(dat);

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
    //Serial.println("fall detected");
    //send data to client
  }
  fall = false;
  c = 0;
  dataIn = "";
}
