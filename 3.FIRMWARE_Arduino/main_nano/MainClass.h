/* This library is for Display memu creation along with input */
#ifndef DISPLAY_ST7920
#define DISPLAY_ST7920

//#include <Arduino.h>
#include <U8g2lib.h>
#include "LM393.h"
#include "mpu6050_imu.h"
#include "SerialCOM.h"
#include "LM35.h"
#include "DFPlayer.h"

#include <SPI.h>


#define SPEAK_STATE       1   // if selected is speak
#define SWITCH_STATE      2   // if selected is switch
#define NURSE_STATE       3   // if selected is speak->Nurse
#define WATER_STATE       4   // if selected is speak->Water
#define MEDICIN_STATE     5  // if selected is speak->Medicin
#define FOOD_STATE        6   // if selected is speak->Food
#define SWITCH1_STATE     7   // if selected is Switch->Fan
#define SWITCH2_STATE     8   // if selected is Switch->Light
#define SWITCH3_STATE     9   // if selected is Switch->Light

#define buttonPin             8  // BACK button
#define buttonConformation    6  // OK button
#define soundPin              7  // Sound sensor Pin

//const char* COMMAND = "CLICK TO...";  // Displaying on main menu screen
//const char*  REQ_COMMAND = "REQUESTING..."; // displaying on requesting speak service menu
float temparature = 0;
//char buff[8] = "27.13";
boolean fallDetected = false;
byte cnt = 0;

/* U8G2 initiation */
//U8G2_ST7920_192X32_F_8080 u8g2(U8G2_R0, 8, 9, 10, 11, 4, 5, 6, 7, /*enable=*/ 18, /*cs=*/ U8X8_PIN_NONE, /*dc=*/ 17, /*reset=*/ U8X8_PIN_NONE);
//U8G2_ST7920_192X32_F_SW_SPI u8g2(U8G2_R0, /* clock=*/ 18 /* A4 */ , /* data=*/ 16 /* A2 */, /* CS=*/ 17 /* A3 */, /* reset=*/ U8X8_PIN_NONE);
//U8G2_ST7920_128X64_F_8080 u8g2(U8G2_R0, 8, 9, 10, 11, 4, 5, 6, 7, /*enable=*/ 18 /* A4 */, /*cs=*/ U8X8_PIN_NONE, /*dc/rs=*/ 17 /* A3 */, /*reset=*/ 15 /* A1 */);  // Remember to set R/W to 0
//U8G2_ST7920_128X64_F_SW_SPI u8g2(U8G2_R0, /* clock=*/ 18 /* A4 */ , /* data=*/ 16 /* A2 */, /* CS=*/ 17 /* A3 */, /* reset=*/ U8X8_PIN_NONE);
//U8G2_ST7920_128X64_F_SW_SPI u8g2(U8G2_R0, /* clock=*/ 13, /* data=*/ 11, /* CS=*/ 10, /* reset=*/ 8);
//U8G2_ST7920_128X64_F_SW_SPI u8g2(U8G2_R0, /* clock=*/ 14, /* data=*/ 13, /* CS=*/ 15, /* reset=*/ 16); // Feather HUZZAH ESP8266, E=clock=14, RW=data=13, RS=CS
U8G2_ST7920_128X64_F_HW_SPI u8g2(U8G2_R2, /* CS=*/ 10, /* reset=*/ 5);
//U8G2_ST7920_128X64_F_HW_SPI u8g2(U8G2_R0, /* CS=*/ 15, /* reset=*/ 16); // Feather HUZZAH ESP8266, E=clock=14, RW=data=13, RS=CS
//U8G2_ST7920_128X64_F_SW_SPI u8g2(U8G2_R2, /* clock=*/ 13, /* data=*/ 10, /* CS=*/ 11, /* reset=*/ 12);
//U8G2_ST7920_128X64_F_SW_SPI u8g2(U8G2_R2, /* clock=*/ 13, /* data=*/ 11, /* CS=*/ 10, /* reset=*/ 5);

LM393 ObjSound(soundPin); // Create Sound sensor object
MPU6050 ObjImu;   // Object for MPU6050, for fall detection */
comComm ObjCOM;   // Serial Communication
lm35  ObjLM35(A3);
DFPlayer music;
/* Class for Display Memu */
class MainClass
{

  public:

    byte Speak_Swt = 0;  // gives seleted speak =1, switch = 2
    byte Speak_Cnt = 0;  // keep track of speak commands
    byte Switch_Cnt = 0; // keep track of switch commands
    byte StateChanged = 0; // gives latest state changed
    bool gotServiceFlag = 0; //gives the ressults of service placed or not
    bool debounce1 = true; // button confirmation for service placed
    bool soundDetected = true; // flag to avoid multiple sound detection
    //const char command_disp[2][10] PROGMEM = {"SPEAK", "SWITCHES"}; // Display on main memu options
    //const char switch_ctrl[3][17] PROGMEM = {"TOGGLE FAN SWT", "TOGGLE LIGHT_1", " TOGGLE LIGHT_2"}; // Toggle switch controls
    //const char speak_ctrl[4][10] PROGMEM = {"NURSE" , "WATER", "MEDICIN", "FOOD"}; //Display on speak service request screen
    byte Cnt = 0;

    void Init()
    {
      ObjSound.Init();    // Begin LM393(soundSensor)
      ObjImu.beginMPU();  // Begin MPU
      ObjCOM.Init();      // Begin NODEMCU Serial
      pinMode(buttonConformation, INPUT);
      //  pinMode(buttonPin, INPUT);  // sound pin  // has to change
      u8g2.begin(); //
      //Serial.begin(9600); // just for debug
      music.begin();

    }

    /* Run Menu */
    void runMenu()
    {
      u8g2.clearBuffer();          // clear the internal memory
      //u8g2.setFont(u8g2_font_profont10_tf); // choose a suitable font
      u8g2.setFont(u8g2_font_ncenB08_tr); // choose a suitable font
      u8g2.setFontDirection(0);
      getSpeak_SwitchCmd();
    }
    void display_delay(int period)
    {

      unsigned long time_now = millis();

      /*********** This block will prints temperture ************/
      temparature = ObjLM35.getTempCelcius();
      u8g2.setCursor(5, 64);
      u8g2.print(F("T:"));
      if (temparature > 0 )
      {
        u8g2.setCursor(15, 64);
        //dtostrf(temparature, 4, 2, buff);
        // u8g2.print(F("27.34"));
        u8g2.print(temparature);
      }

      // u8g2.setCursor(64, 64);
      // u8g2.print(fallVal);

      u8g2.sendBuffer();

      /***********************************************************/

      while (millis() < (time_now + period)) {
        //wait approx. [period] ms

        /* This block is for fall detection */
        ObjImu.detectFall(&fallDetected);
        if (fallDetected == true)
        { // Problem causing at here
          Fall_Detected();    // Uncommenting this cause flikeeing problem
          fallDetected = false;
          //break;
        }

        if (ObjSound.readSoundSens() == 0 && soundDetected == false) //Read Sound Sensor state outputs 1 when sound detected
        {
          soundDetected = true;
          //Serial.println("Sound detected");
          if (Speak_Cnt == 0 && Switch_Cnt == 0) // when no switch/speak commands are selected
          {
            switch (Speak_Swt)
            {
              //Serial.println(Speak_Swt);
              case 1: StateChanged = SPEAK_STATE;
                break;
              case 2: StateChanged = SWITCH_STATE;
                break;
              default: ;// do nothing
            }
          }

          // Speak controls selection
          switch (Speak_Cnt)
          {
            case 1: StateChanged = NURSE_STATE;
              break;
            case 2: StateChanged = WATER_STATE;
              break;
            case 3: StateChanged = MEDICIN_STATE;
              break;
            case 4: StateChanged = FOOD_STATE;
              break;
            default: ;// do nothing
          }

          // Switch controls selection
          switch (Switch_Cnt)
          {
            case 1: StateChanged = SWITCH1_STATE;
              break;
            case 2: StateChanged = SWITCH2_STATE;
              break;
            case 3: StateChanged = SWITCH3_STATE;
              break;
            default: ;// do nothing
          }

          //break; // break while loop is sound detected
        }
      }// end of while
    }


    void getSpeak_SwitchCmd()
    {
      while (1)
      {
        u8g2.setCursor(30, 25);
        u8g2.print(F("CLICK TO..."));
        u8g2.setCursor(35, 45);
        if (Speak_Swt == 0)
        { u8g2.print(F("SPEAK"));
        }
        else {
          u8g2.print(F("SWITCH"));
        }
        Speak_Swt++;
        u8g2.sendBuffer();          // transfer internal memory to the display
        display_delay(2000);    // millis to wait
        u8g2.clearBuffer();
        soundDetected = false; // Disable flag for sound detection

        if (StateChanged == SPEAK_STATE)
        {
          getSpeakCmds();
        }
        else if (StateChanged == SWITCH_STATE)
        {
          getSwitchCmds();
        }

        temparature = 0; // it has to be removed after replacing perfect temparature sensor
        /* If Temparature Grater then 35 deg Turn On Fan */
        if (temparature > 35.0)
        {
          //Turn_On_FAN("TOGGLE FAN");
        }

        if (Speak_Swt == 2)
          Speak_Swt = 0;

        if (gotServiceFlag == 1)
        {
          StateChanged = 0;  // Got service get out of speak commands loop
          Switch_Cnt = 0;
          Speak_Cnt = 0;
        }

        gotServiceFlag = 0; // clear service flag if it set

      }
    }

    // Speak or Switches
    void getSpeakCmds()
    {
      fallDetected = false;

      u8g2.setFont(u8g2_font_ncenB08_tr);  // choose a suitable font
      Speak_Cnt = 0; // clear switch count
      while (1)
      {
        u8g2.clearBuffer();
        u8g2.setCursor(20, 40);
        u8g2.print(F("REQUESTING..."));

        u8g2.setCursor(45, 55);
        if (Speak_Cnt == 0)
        {
          u8g2.print(F("NURSE"));  // write something to the internal memory
        }
        else if (Speak_Cnt == 1)
        {
          u8g2.print(F("WATER"));  // write something to the internal memory
        }
        else if (Speak_Cnt == 2)
        {
          u8g2.print(F("MEDICINE"));  // write something to the internal memory
        }
        else
        {
          u8g2.print(F("FOOD"));  // write something to the internal memory
        }
        Speak_Cnt++; //increment speak menu count
        u8g2.sendBuffer();          // transfer internal memory to the display
        display_delay(2000);

        soundDetected = false; // Disable flag for sound detection
        //Serial.print("state : ");
        //Serial.println(StateChanged);
        switch (StateChanged)
        {
          case NURSE_STATE : waitForServiceConformation(Speak_Cnt);
            break;
          case WATER_STATE : waitForServiceConformation(Speak_Cnt);
            break;
          case MEDICIN_STATE : waitForServiceConformation(Speak_Cnt);
            break;
          case FOOD_STATE : waitForServiceConformation(Speak_Cnt);
            break;
          default: ;// do nothing
        }

        if (Speak_Cnt == 4)
          Speak_Cnt = 0;

        if (gotServiceFlag == 1)
          break;  // Got service get out of speak commands loop

        u8g2.clearBuffer();
      }

    }


    /* loop for switch commands */
    void getSwitchCmds()
    {
      //u8g2.setFont(u8g2_font_ncenB08_tr);  // choose a suitable font
      u8g2.clearBuffer();
      u8g2.setFont(u8g2_font_ncenB08_tr);  // choose a suitable font
      Switch_Cnt = 0; // clear switch count

      while (1)
      {
        //   u8g2.drawStr(30,40,command_disp[Speak_Swt++]);
        u8g2.setCursor(20, 30);
        u8g2.print(F("REQUESTING...")); // request for


        u8g2.setCursor(10, 45);
        if (Switch_Cnt == 0)
        {
          u8g2.print(F("To Switch FAN"));  // write something to the internal memory
        }
        else if (Switch_Cnt == 1)
        {
          u8g2.print(F("To Switch Light1"));  // write something to the internal memory
        }
        else
        {
          u8g2.print(F("To Switch Light2"));  // write something to the internal memory
        }
        Switch_Cnt++;
        u8g2.sendBuffer();          // transfer internal memory to the display
        display_delay(1000);
        //u8g2.drawStr(30,40," ");

        soundDetected = false; // Disable flag for sound detection

        //Serial.print("state : ");
        //Serial.println(StateChanged);
        switch (StateChanged)
        {
          case SWITCH1_STATE : SendToggleSwitch(Switch_Cnt);
            break;
          case SWITCH2_STATE : SendToggleSwitch(Switch_Cnt);
            break;
          case SWITCH3_STATE : SendToggleSwitch(Switch_Cnt);
            break;
          default: ;// do nothing
        }

        if (Switch_Cnt == 3)
          Switch_Cnt = 0;

        if (gotServiceFlag == 1)
          break;  // Got service get out of speak commands loop

        u8g2.clearBuffer();
      }


    }


    /* Wait for pop up service confirmation */
    void waitForServiceConformation(int requested_service)
    {
      u8g2.setFont(u8g2_font_ncenB08_tr);  // choose a suitable font
      Cnt = 0; // used for alternative prints
      unsigned long waitStartTime = millis();
      while ( millis() < (waitStartTime + 120000) ) // Wait For 2 Minutes to get Service, Set Accourding to ua Service Wait Time (for minute : 60* 1000)
      {
        u8g2.clearBuffer();

        //   u8g2.drawStr(30,40,command_disp[Speak_Swt++]);
        u8g2.setCursor(20, 20);
        u8g2.print(F("REQUESTED"));

        u8g2.setCursor(45, 30);
        if (requested_service - 1 == 0)
        {
          u8g2.print(F("NURSE"));  // write something to the internal memory
          music.DFPlay(8);
        }
        else if (requested_service - 1 == 1)
        {
          u8g2.print(F("WATER"));  // write something to the internal memory
          music.DFPlay(5);
        }
        else if (requested_service - 1 == 2)
        {
          u8g2.print(F("MEDICINE"));  // write something to the internal memory
          music.DFPlay(1);
        }
        else
        {
          u8g2.print(F("FOOD"));  // write something to the internal memory
          music.DFPlay(4);
        }

        if (Cnt++ % 2 == 0) // making it to blink
        {
          u8g2.setCursor(5, 45);
          u8g2.print(F("DID YOU GET"));
          u8g2.setCursor(45, 55);
          u8g2.print(("SERVICE ?"));  // write something to the internal memory
          u8g2.sendBuffer();
        }

        u8g2.sendBuffer();          // transfer internal memory to the display

        /* Play Music through speaker */
        //Play requested_service);

        /* This below block will  wait for service Confirm button press */
        unsigned long time_now = millis();
        while (millis() < (time_now + 3000)) {

          if (digitalRead(buttonConformation) == LOW  && debounce1 == true) //Button 1 Pressed
          {
            debounce1 = false;
            gotServiceFlag = 1;
          }

          if (gotServiceFlag == 1)
            break;  // Got service get out of wait loop
        }
        //Serial.println("CAME HERE 2");
        if (digitalRead(buttonConformation) == HIGH) //Avoid debounce
          debounce1 = true;

        if (gotServiceFlag == 1)
        {
          music.DFPlay(9);
          u8g2.clearBuffer();

          break;
        }// Got service get out of wait conformation loop

        u8g2.clearBuffer();
      } // end of While Loop

      if (gotServiceFlag == 0)
      {
        //Serial.println(F("Failed To Get Service"));

        gotServiceFlag = 1; // enable so that go to init stage
      }

    }


    void SendToggleSwitch(int requested_service)
    {
      //   u8g2.drawStr(30,40,command_disp[Speak_Swt++]);
      for (byte i = 0; i < 7; i++)
      {
        u8g2.clearBuffer();
        u8g2.setCursor(20, 20);
        u8g2.print(F("REQUESTED"));

        if (i % 2 == 0)
        {
          u8g2.setCursor(15, 35);
          //          u8g2.print(switch_ctrl[requested_service - 1]); // write something to the internal memory
          if (requested_service - 1 == 0)
          {
            u8g2.print(F("To Switch FAN"));  // write something to the internal memory
            music.DFPlay(3);
          }
          else if (requested_service - 1 == 1)
          {
            u8g2.print(F("To Switch Light1"));  // write something to the internal memory
            music.DFPlay(6);
          }
          else
          {
            u8g2.print(F("To Switch Messenger"));  // write something to the internal memory
            music.DFPlay(7);
          }
          //REVISIT THIS TO SEND COMMANDS TO NODEMCU
          //ObjCOM.ToggleSW(switch_ctrl[requested_service - 1]);
        }
        // Send This to Wifi Thrice from here
        u8g2.sendBuffer();
        //    display_delay(1000);

        /* This below block will  wait for service Confirm button press */
        unsigned long time_now = millis();
        while (millis() < (time_now + 2000)) {
        }
        /*
          unsigned long time_now = millis();
          while(millis() < (time_now + 1000)){
          // wait for some time
          i = i;
          }*/

        u8g2.clearBuffer();
        /*time_now = millis();
          while(millis() < (time_now + 1000)){
          // wait for some time
          i = i;
          }*/
      }

      gotServiceFlag = 1; // set got service flag
      u8g2.clearBuffer();
    }


    /** When Room Temparature got high turn On Fan */
    void Turn_On_FAN(char *data)
    {
      //    ObjCOM.ToggleSW(data);

    }

    void Fall_Detected()
    {
      /* This is to send mesg to indicate Fall detected */
      //      ObjCOM.ToggleSW(F("FALL DETECTED"));
      u8g2.clearBuffer();
      u8g2.setCursor(20, 20);
      u8g2.print(F("NEED HELP!"));
      u8g2.setCursor(10, 40);
      u8g2.print(F("I FELL DOWN!"));
      u8g2.sendBuffer();
      //play requesting for fall service
      music.DFPlay(2);
      delay(4000);
      music.DFPlay(2);
      delay(4000);
      music.DFPlay(2);
      delay(4000);
      music.DFPlay(2);
      delay(4000);
    }


}; // end of class





#endif
