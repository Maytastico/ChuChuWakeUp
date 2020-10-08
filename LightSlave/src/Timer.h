
#ifndef TIMER_H_
#define TIMER_H_

#include <Arduino.h>


class Timer
{
private:
  unsigned long timerStart = 0;
  unsigned long timerTarget = 0;

public:
  void startTimer(long msec)
  {
    timerStart = millis();
    timerTarget = msec;
  }

  bool isTimerReady()
  {
    return (millis() - timerStart) > timerTarget;
  }
};

#endif // TIMER_H_
