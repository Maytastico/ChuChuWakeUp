#ifndef RAINBOW_H_
#define RAINBOW_H_


#include <Arduino.h>
#include <ARGB.h>
#include <Timer.h>
#include <ProgramManager.h>
#include <Adafruit_NeoPixel.h>

class ARGB;


class Rainbow{
    private:
        uint32_t firstHue = 0;

        ARGB *p_argb = nullptr;

        ProgramManager *p_program = nullptr;

        Timer refreshStripe;

        ChangeColor brightnessState = STDBY;

    public:
        Rainbow(){}

        void setARGB(ARGB *_argb, ProgramManager* program){
             this->p_argb = _argb;
             this->p_program = program;
        };
        void changeToRainbow();
        void setRainbow();
        void evaluateHue();
        void loop();
};

#endif //RAINBOW_H_