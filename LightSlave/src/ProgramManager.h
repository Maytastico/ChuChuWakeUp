#ifndef ProgramManager_H_
#define ProgramManager_H_

#include <Arduino.h>
#include <EpromHandler.h>

/**
     * Contains possible light programs/animation that can be played
     */
    enum Program{
      OFF,
      SET_MANUEL_COLOR,
      RAINBOW,
      RANDOM,
    };

class ProgramManager{
  private:
    uint16_t updateRate = 100;

    Program currentProgram = OFF;

    EpromHandler *storage = nullptr;

  public:
    ProgramManager(){}

    void setStore(EpromHandler *storage);

    uint16_t getUpdateRate();

    Program getCurrentProgram();

    void setProgram(Program programType);

    void setUpdateRateRelative(int16_t step);

      

    

};

#endif // ProgramManager_H_