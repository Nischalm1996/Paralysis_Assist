#ifndef SERIAL_COM
#define SERIAL_COM

/*
 * This is file is for making serial communication to send commands to ESP8266 
 */
class comComm
{
  public :
   void Init()
   {
    Serial.begin(9600);
   }

   void ToggleSW(char *data)
   {
    Serial.print('*');Serial.print(data);Serial.print('X');
   }
};

#endif
