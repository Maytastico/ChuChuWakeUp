#ifndef RAINBOW_H_
#define RAINBOW_H_

#include <ARGB.h>
#include <Arduino.h>
#include <Timer.h>
#include <ProgramManager.h>
#include <Adafruit_NeoPixel.h>

class ARGB;

class Rainbow
{
private:
    enum Animation
    {
        STBY=0,
        FADE_OUT,
        SET_FIRST,
        PLAY,
    };
    uint32_t firstHue = 0;

    ARGB *p_argb = nullptr;

    ProgramManager *p_program = nullptr;

    Timer refreshStripe;

    Animation animationState;

    void changeToRainbow();

public:
    Rainbow() {}

    void setARGB(ARGB *_argb, ProgramManager *program)
    {
        this->p_argb = _argb;
        this->p_program = program;
    };

    void setRainbow();
    void evaluateHue();
    void start();
    void stop();
    void loop();
};

#endif //RAINBOW_H_