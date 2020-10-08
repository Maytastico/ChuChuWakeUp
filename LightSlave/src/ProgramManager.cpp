#include <ProgramManager.h>

uint16_t ProgramManager::getUpdateRate(){
    return updateRate;
}

Program ProgramManager::getCurrentProgram(){
    return currentProgram;
}

void ProgramManager::setUpdateRateRelative(int16_t step){
    int32_t actUpdateRate = (uint16_t)updateRate + step;

    if(actUpdateRate < 70){
        updateRate = 70;
    }else if(actUpdateRate>65536){
        updateRate = 65536;
    }else
    {
        updateRate = actUpdateRate;
    }
}

void ProgramManager::setProgram(Program newProgram){
    currentProgram = newProgram;
}