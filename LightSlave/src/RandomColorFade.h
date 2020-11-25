#ifndef RANDOMCOLORFADE_H_
#define RANDOMCOLORFADE_H_

#include <Arduino.h>
#include <ARGB.h>
#include <Timer.h>

class ARGB;

class RandomColorFade
{
private:
    
    Timer ChangeColor;

    ARGB *p_argb;

public:
    
    RandomColorFade(){}
    
    //Initializes Effect
    void begin(ARGB *_argb){
        p_argb = _argb;
    }

    long generateTime();

    void loop(void);
};

#endif //RANDOMCOLORFADE_H_