/****************************************************************************************************************************************************
 *  TITLE: ESP-NOW Getting Started Examples
 *
 *  By Frenoy Osburn
 *  YouTube Video: https://youtu.be/_cNAsTB5JpM
 ****************************************************************************************************************************************************/

 /********************************************************************************************************************
  * Please make sure that you install the board support package for the ESP8266 boards.
  * You will need to add the following URL to your Arduino preferences.
  * Boards Manager URL: http://arduino.esp8266.com/stable/package_esp8266com_index.json
 ********************************************************************************************************************/
 
 /********************************************************************************************************************
 *  Board Settings:
 *  Board: "WeMos D1 R1 or Mini"
 *  Upload Speed: "921600"
 *  CPU Frequency: "80MHz"
 *  Flash Size: "4MB (FS:@MB OTA:~1019KB)"
 *  Debug Port: "Disabled"
 *  Debug Level: "None"
 *  VTables: "Flash"
 *  IwIP Variant: "v2 Lower Memory"
 *  Exception: "Legacy (new can return nullptr)"
 *  Erase Flash: "Only Sketch"
 *  SSL Support: "All SSL ciphers (most compatible)"
 *  COM Port: Depends *On Your System*
 *********************************************************************************************************************/
 #include<ESP8266WiFi.h>
#include<espnow.h>

#define MY_NAME   "SLAVE_NODE"
#define l1 16
#define l2 5
#define l3 4




struct __attribute__((packed)) dataPacket {
  boolean light1;
  boolean light2;
  boolean light3;
  boolean fall;
};
static dataPacket packet;  

void dataReceived(uint8_t *senderMac, uint8_t *data, uint8_t dataLength) {
  char macStr[18];

  snprintf(macStr, sizeof(macStr), "%02x:%02x:%02x:%02x:%02x:%02x", senderMac[0], senderMac[1], senderMac[2], senderMac[3], senderMac[4], senderMac[5]);

  Serial.println();
  Serial.print("Received data from: ");
  Serial.println(macStr);
  
  memcpy(&packet, data, sizeof(packet));
  
  Serial.print("light1: ");
  Serial.println(packet.light1);
  Serial.println(l1);
  Serial.print("light2: ");
  Serial.println(packet.light2);
  Serial.println(l2);
  Serial.print("light3: ");
  Serial.println(packet.light3);
  Serial.println(l3);
    Serial.print("fall: ");
  Serial.println(packet.fall);
 
}
void setup() {
    
  Serial.begin(9600);     // initialize serial port

  Serial.println();
  Serial.println();
  Serial.println();
  Serial.print("Initializing...");
  Serial.println(MY_NAME);
  Serial.print("My MAC address is: ");
  Serial.println(WiFi.macAddress());
  
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();        // we do not want to connect to a WiFi network

  pinMode(l1,OUTPUT);
  pinMode(l2,OUTPUT);
  pinMode(l3,OUTPUT);
  
  if(esp_now_init() != 0) {
    Serial.println("ESP-NOW initialization failed");
    return;
  }

  esp_now_register_recv_cb(dataReceived);   // this function will get called once all data is sent

  Serial.println("Initialized.");
}

void loop() {
   digitalWrite(l1,packet.light1);
  digitalWrite(l2,packet.light2);
  digitalWrite(l3,packet.light3);
 if(packet.fall==1)
 {
  Serial.println("send a msg to wtsapp");
}
}
