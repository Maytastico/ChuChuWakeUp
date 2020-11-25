#include <RandomColorFade.h>

long RandomColorFade::generateTime(){
    return random(2000, 60000);
}

void RandomColorFade::loop(){
    if(this->ChangeColor.isTimerReady()){
        this->ChangeColor.startTimer(this->generateTime());
        p_argb->changeColor(p_argb->generateRandomColor());
    }
}