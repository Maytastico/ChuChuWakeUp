#include <SerialHandler.h>
#include <string.h>

void SerialHandler::loop()
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
            SerialHandler::parseCommands(incomingData);
        }
    }
}

void SerialHandler::parseCommands(String dataFromInterface)
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
        else if (data[i] == ',' && flag == ARGUMENTS)
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
        else if (flag == ARGUMENTS)
        {
            arguments[argumentCounter] += data[i];
        }
    }

    this->command = command;
    for (size_t i = 0; i < 3; i++)
    {
        this->arguments[i] = arguments[i];
    }

    

    this->commandAvailable = true;
}

bool SerialHandler::dataAvailable()
{
    if (this->commandAvailable == true)
    {
        this->commandAvailable = false;
        return true;
    }
    return false;
}

void SerialHandler::printOutSerialData(){
    /* Debugger*/
    Serial.println("Command: " + String(this->command));
    for (size_t i = 0; i < 3; i++)
    {
        Serial.println("Arguments: " + String(this->arguments[i]));
    }
}

String* SerialHandler::getArguments(){
    return this->arguments;
}

String SerialHandler::getCommand(){
    return this->command;
}