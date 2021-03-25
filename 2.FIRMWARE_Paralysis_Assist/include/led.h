#ifndef _LED_H
#define _LED_H

int redPin = 11;   // red pin is connected to 11
int greenPin = 10; // green pin is connected to 10
int bluePin = 9;   // blue pin is connected to 9
class ledin
{
public:
    int ledin;

    void beginled()
    {

        pinMode(redPin, OUTPUT); // set all three pins as outputs
        pinMode(greenPin, OUTPUT);
        pinMode(bluePin, OUTPUT);
    }
    void runled()
    {
        {
            setColor(255, 0, 0); // red
            delay(1000);         // wait one second
            setColor(0, 255, 0); // green
            delay(1000);         // wait one second
            setColor(0, 0, 255); // blue
            delay(1000);         // wait one second
        }
        void setColor(int red, int green, int blue)
        {
            // set the three pins:
            analogWrite(redPin, red);     // brightness of redPin
            analogWrite(greenPin, green); // brightness of greenPin
            analogWrite(bluePin, blue);   // brightness of bluePin
        }
    }
#endif