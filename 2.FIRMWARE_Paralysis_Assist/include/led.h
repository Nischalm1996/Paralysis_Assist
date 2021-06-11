#include "Arduino.h"
#ifndef _LED_H
#define _LED_H

int redPin = A2;   // red pin is connected to 11
int greenPin = A1; // green pin is connected to 10
int bluePin = A0;  // blue pin is connected to 9

class LEDClass
{
public:
    int ledin;

    void beginled()
    {

        pinMode(redPin, OUTPUT); // set all three pins as outputs
        pinMode(greenPin, OUTPUT);
        pinMode(bluePin, OUTPUT);
    }
    void demoLed()
    {

        // setColor(255, 0, 0); // red
        // delay(500);         // wait one second
        // setColor(0, 255, 0); // green
        // delay(500);         // wait one second
        // setColor(0, 0, 255); // blue
        // delay(500);         // wait one second
        // setColor(255, 255, 255); // blue
        // delay(500);         // wait one second
        setColor(0, 0, 0); // red
        int i, j, k;
        for (i = 0; i < 200;i=i+10)
        {
            for (j = 0; j < 200;j=j+10)
            {
                for (k = 0; k < 200;k=k+10)
                {
                    analogWrite(redPin, i);     // brightness of redPin
                    analogWrite(greenPin, j); // brightness of greenPin
                    analogWrite(bluePin, k);  // brightness of bluePin;
                    delayMicroseconds(40);
                }
            }
        }
        setColor(0, 0, 0); // red
    }
    void setColor(int red, int green, int blue)
    {
        // set the three pins:
        analogWrite(redPin, red);     // brightness of redPin
        analogWrite(greenPin, green); // brightness of greenPin
        analogWrite(bluePin, blue);   // brightness of bluePin
    }

};
#endif