#ifndef _SOUNDIN_H
#define _SOUNDIN_H

class soundIn
{
public:
    int Sound_inp;

    void beginSound(int inp_pin)
    { // to be put in void setup; initiates the sound sensor

        Sound_inp = inp_pin;
        pinMode(Sound_inp, INPUT);
        pinMode(LED_BUILTIN, OUTPUT);
    }

    void runSoundSensor() // to be put in loop and runs the sound condition
    {
        int Sound = digitalRead(Sound_inp);

        if (Sound == HIGH)
        {
            digitalWrite(LED_BUILTIN, HIGH);
        }
        else
        {
            digitalWrite(LED_BUILTIN, LOW);
        }
        delay(1);
    }
};
#endif