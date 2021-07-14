#ifndef _callBot_H
#define _callBot_H

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
const char *ssid = "Nischal.M";
const char *password = "nischal@001743";

class callBot
{
  public:
    void begin()
    {
      Serial.begin(9600);
      WiFi.begin(ssid, password);

      while (WiFi.status() != WL_CONNECTED)
      {
        delay(500);
        Serial.print(".");
      }
//      Serial.println("");
//      Serial.println("WiFi connected");
//      Serial.println("IP address: ");
//      Serial.println(WiFi.localIP());
    }
    void sendWhatsappMessage()
    {
      Serial.begin(9600);

      HTTPClient http;
      WiFiClient client;
      String apiGetData = "http://api.callmebot.com/whatsapp.php?phone=+919741678014&text=THE+PATIENT+FELL+DOWN+KINDLY+HELP&apikey=614074";
      //Serial.println("Sending: " + apiGetData);
      http.begin(client, apiGetData);

      int httpCode = http.GET(); //Send the request
      if (httpCode > 0)
      {
        //Check the returning code
        String payload = http.getString(); //Get the request response payload
        //Serial.println(payload); //Print the response payload
      }
      http.end();
    }
};
#endif
