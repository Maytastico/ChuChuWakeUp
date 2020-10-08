#pragma once
#ifndef SERIALHANDLER_H_
#define SERIALHANDLER_H_

#include <Arduino.h>

class SerialHandler
{
private:
    String command;
    String arguments[3];

public:
    SerialHandler(){};
    uint8_t loop();
    uint8_t parseCommands(String data);
};

#endif // SERIALHANDLER_H_