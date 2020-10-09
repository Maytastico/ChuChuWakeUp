#pragma once
#ifndef SERIALHANDLER_H_
#define SERIALHANDLER_H_

#include <Arduino.h>

class SerialHandler
{
private:
    String command;
    String arguments[3];
    bool commandAvailable;

public:
    SerialHandler(){};
    void loop();
    void parseCommands(String data);
    bool dataAvailable();
    void printOutSerialData();
};

#endif // SERIALHANDLER_H_