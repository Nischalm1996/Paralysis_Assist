/****************************************************************************************************************************************************
    TITLE: ESP-NOW Getting Started Examples

    By Frenoy Osburn
    YouTube Video: https://youtu.be/_cNAsTB5JpM
 ****************************************************************************************************************************************************/

/********************************************************************************************************************
   Please make sure that you install the board support package for the ESP8266 boards.
   You will need to add the following URL to your Arduino preferences.
   Boards Manager URL: http://arduino.esp8266.com/stable/package_esp8266com_index.json
********************************************************************************************************************/

/********************************************************************************************************************
   Board Settings:
   Board: "WeMos D1 R1 or Mini"
   Upload Speed: "921600"
   CPU Frequency: "80MHz"
   Flash Size: "4MB (FS:@MB OTA:~1019KB)"
   Debug Port: "Disabled"
   Debug Level: "None"
   VTables: "Flash"
   IwIP Variant: "v2 Lower Memory"
   Exception: "Legacy (new can return nullptr)"
   Erase Flash: "Only Sketch"
   SSL Support: "All SSL ciphers (most compatible)"
   COM Port: Depends *On Your System
*********************************************************************************************************************/
#include<ESP8266WiFi.h>
#include<espnow.h>
#include"callBot.h"


#define MY_NAME         "MASTER_NODE"
#define MY_ROLE         ESP_NOW_ROLE_CONTROLLER         // set the role of this device: CONTROLLER, SLAVE, COMBO
#define RECEIVER_ROLE   ESP_NOW_ROLE_SLAVE              // set the role of the receiver
#define WIFI_CHANNEL    1
uint8_t receiverAddress[] = {0x48, 0x3F, 0xDA, 0xA3, 0x80, 0x76};   // please update this with the MAC address of the receiver
callBot wtsMsg;

struct __attribute__((packed)) dataPacket {
  boolean light1;
  boolean light2;
  boolean light3;
  boolean fall;
};
static dataPacket packet;

char c = 0;
String dataIn = "";
void transmissionComplete(uint8_t *receiver_mac, uint8_t transmissionStatus) {
  if (transmissionStatus == 0) {
    Serial.println("Data sent successfully");
  } else {
    Serial.print("Error code: ");
    Serial.println(transmissionStatus);
  }
}
void serialOp()
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

  String dat = dataIn.substring (indexofS + 1 , indexofx);
  //Serial.print("Dat:"); Serial.println(dat);

  if (dat == "1")
  {
    packet.light1 = !packet.light1;
    esp_now_send(receiverAddress, (uint8_t *) &packet, sizeof(packet));

  }
  if (dat == "2")
  {
    packet.light2 = !packet.light2;
    esp_now_send(receiverAddress, (uint8_t *) &packet, sizeof(packet));

  }
  if (dat == "3")
  {
    packet.light3 = !packet.light3;
    esp_now_send(receiverAddress, (uint8_t *) &packet, sizeof(packet));

  }
  if (dat == "4")
  {
    packet.fall = true;
    Serial.println("fall detected");
    wtsMsg.sendWhatsappMessage();
    esp_now_send(receiverAddress, (uint8_t *) &packet, sizeof(packet));

    //send data to client
  }
  packet.fall = false;
  esp_now_send(receiverAddress, (uint8_t *) &packet, sizeof(packet));
  c = 0;
  dataIn = "";
}
void setup() {
  Serial.begin(9600);     // initialize serial port
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();        // we do not want to connect to a WiFi network
   wtsMsg.begin();

  if (esp_now_init() != 0) {
    Serial.println("ESP-NOW initialization failed");
    return;

    packet.light1 = false;
    packet.light2 = false;
    packet.light3 = false;
    packet.fall = false;
  }

  esp_now_set_self_role(MY_ROLE);
  esp_now_register_send_cb(transmissionComplete);   // this function will get called once all data is sent
  esp_now_add_peer(receiverAddress, RECEIVER_ROLE, WIFI_CHANNEL, NULL, 0);

  Serial.println("Initialized.");
}

void loop() {
  serialOp();
  delay(3000);
}
