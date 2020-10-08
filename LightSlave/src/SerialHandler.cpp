#include <SerialHandler.h>
#include <string.h>

uint8_t SerialHandler::loop()
{
    if (Serial.available() > 1)
    {
        String incomingData = Serial.readString();
        if (incomingData.length() < 5)
        {
            Serial.println("Not valid!");
        }
        else
        {
            if(SerialHandler::parseCommands(incomingData)>0){
                return 1;
            }
        }
    }
}

uint8_t SerialHandler::parseCommands(String dataFromInterface)
{
    int n = dataFromInterface.length();
    char data[n + 1];

    strcpy(data, dataFromInterface.c_str());
    enum CommandFlag
    {
        COMMAND,
        ARGUMENTS,
    };

    String command;
    String arguments[3];

    int argumentCounter = 0;

    CommandFlag flag = COMMAND;
    for (size_t i = 0; i < n; ++i)
    {
        if (data[i] == '(' || data[i] == ')')
        {
            flag = ARGUMENTS;
            continue;
        }

        if (data[i] == ',' && flag == ARGUMENTS)
        {
            if (argumentCounter <= 3)
            {
                argumentCounter++;
                continue;
            }
            else
            {
                Serial.println("To many arguments! Just three arguments allowed");
            }
        }

        if (flag == COMMAND)
        {
            command += data[i];
        }

        if (flag == ARGUMENTS)
        {
            arguments[argumentCounter] += data[i];
        }
    }

    SerialHandler::command = command;
    for (size_t i = 0; i < 3; i++)
    {
        SerialHandler::arguments[i] = arguments[i];
    }
    return 1;
    /* Debugger*/
    /* Serial.println("Command: " + String(SerialHandler::command));
    for (size_t i = 0; i < 3; i++)
    {
        Serial.println("Arguments: " + String(SerialHandler::arguments[i]));
    } */ 
}