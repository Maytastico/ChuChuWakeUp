#include <Arduino.h>
#include <ARGB.h>
#include "EpromHandler.h"
#include <IRremote.h>
#include <IRReceiver.h>
#include <Rainbow.h>
#include <ProgramManager.h>
#include <SerialHandler.h>

const byte LED_Pin = 6;
const uint8_t IR_Pin = 5; //11;
const uint8_t PowerOn_Pin = 7;
const uint16_t numPixels = 50;

// EEPROM Handler
EpromHandler myStore;

//IR Control Objects
IRrecv irrecv(IR_Pin);

//Handles Received Data;
IRReceiver myIr(&irrecv);

//Handles Neopixel
ARGB pixels(numPixels, LED_Pin, &myStore, NEO_GRB + NEO_KHZ800);

//Contains the rainbow program that goes throu the whole
Rainbow rainBowProgram;

//Manages the Programs
ProgramManager programMgr;

//Manages Serial communication
SerialHandler serial;

void setup()
{
  // Loaded data from EEPROM
  uint8_t loadBrightness;
  uint32_t loadColor;

  programMgr.setProgram(SET_MANUEL_COLOR);

  // Set the power on pin as output and switch on
  pinMode(PowerOn_Pin, OUTPUT);
  digitalWrite(PowerOn_Pin, true);

  rainBowProgram.setARGB(&pixels, &programMgr);
  // Initialize Serial Connection
  Serial.begin(9600);

  // Initialize EEPROM
  myStore.begin();
  myStore.getLightData(&loadBrightness, &loadColor);

  // Initialize IR Receiver
  myIr.begin();

  // Initialize ARGB Libery
  pixels.begin();
  pixels.setupARGB(loadBrightness, loadColor);
}

void processIRCommand();
void processSerialCommand();

void loop()
{
  // receive and decode IR data
  if (myIr.isDataReady())
  {
    processIRCommand();
  } // End  if (myIr.isDataReady())

  serial.loop();
  if (serial.dataAvailable() == true)
  {
    processSerialCommand();
  }

  //pixels.changeColor(255, 200, 119);

  if (programMgr.getCurrentProgram() == SET_MANUEL_COLOR)
    // execution of the ARGB Stripe state machine
    pixels.loop();
  else if (programMgr.getCurrentProgram() == RAINBOW)
    rainBowProgram.loop();

  // storing actual brightness to EEPROM
  if (pixels.isStoringRequested() == true)
  {
    myStore.storeBrightness(pixels.getBrightness());
    pixels.resetStoringRequest();
  }

} // end of loop

void processSerialCommand()
{
  String command = serial.getCommand();
  String *arguments = serial.getArguments();

  if (command == "setColor" || command == "setColorFade")
  {
    int r, g, b;
    r = arguments[0].toInt();
    g = arguments[1].toInt();
    b = arguments[2].toInt();
    if (r == 0 && g == 0 && b == 0)
    {
      r = 1;
      g = 1;
      b = 1;
    }
    else if (r > 255 || g > 255 || b > 255)
    {
      if (r > 255)
        r = 255;
      if (g > 255)
        g = 255;
      if (b > 255)
        b = 255;
    }

    //Serial.println("Red: " + String(r) + ", Green: " + String(g) + ", Blue: " + String(b));
    programMgr.setProgram(SET_MANUEL_COLOR);
    if (command == "setColor")
      pixels.setColor(r, g, b);
    else if (command == "setColorFade")
      pixels.changeColor(pixels.Color(r, g, b));
  }
  else if (command == "playAnimation")
  {
    if (arguments[0] == "rainbow")
    {
      programMgr.setProgram(RAINBOW);
    }
    else if (arguments[0] == "manuel")
    {
      programMgr.setProgram(SET_MANUEL_COLOR);
    }
    else
    {
      Serial.println("Program does not exist!");
    }
  }
  else if (command == "setBrightness")
  {
    int brightness = arguments[0].toInt();
    if (brightness > 0 && brightness < 256)
    {
      pixels.setBrightnes(brightness);
    }
  }
  else
  {
    Serial.println("unkown command!");
  }

  Serial.println(command);
}

//Executes the program changes with the commands that were delivered by the IR module
void processIRCommand()
{
  uint32_t data = myIr.getEncodedData();

  // Command : Change to green color
  if (data == TOGGLE_POWER)
  {
    pixels.toggleStripe();
  }
  else if (data == INCREASE_SPEED)
  {
    programMgr.setUpdateRateRelative(-10);
  }
  else if (data == DEINCREASE_SPEED)
  {
    programMgr.setUpdateRateRelative(10);
  }
  else if (data == GREEN_COLOR)
  {
    // store and request a change of color
    myStore.storeColor(pixels.Color(0, 255, 0));
    pixels.changeColor(0, 255, 0);
  }
  // Command : Change to red color
  else if (data == RED_COLOR)
  {
    // store and request a change of color
    myStore.storeColor(pixels.Color(255, 0, 0));
    pixels.changeColor(255, 0, 0);
  }
  // Command : Changes color to blue
  else if (data == BLUE_COLOR)
  {
    // store and request a change of color
    myStore.storeColor(pixels.Color(0, 0, 255));
    pixels.changeColor(0, 0, 255);
  }
  // Command : Changes color to Orange
  else if (data == ORAGNE_COLOR)
  {
    // store and request a change of color
    myStore.storeColor(0xFFBF00);
    pixels.changeColor(0xFFBF00);
  }
  // Command : Changes color to blue
  else if (data == LIME_COLOR)
  {
    // store and request a change of color
    myStore.storeColor(pixels.Color(10, 223, 100));
    pixels.changeColor(10, 223, 100);
  }
  // Command : Changes color to light blue
  else if (data == LIGHT_BLUE_COLOR)
  {
    // store and request a change of color
    myStore.storeColor(pixels.Color(27, 229, 229));
    pixels.changeColor(27, 229, 229);
  } // Command : Changes color to white
  else if (data == WHITE)
  {
    // store and request a change of color
    myStore.storeColor(pixels.Color(255, 255, 255));
    pixels.changeColor(255, 255, 255);
  }
  // Command : Increase brightness
  else if (data == BRIGHT_UP)
  {
    // increase brightness, after 5s store value to EEPROM
    pixels.setBrightnessRelative(BRIGHTNESS_OFFSET);
  }
  // Command : Decrease brightness
  else if (data == BRIGHT_DOWN)
  {
    // decrease brightness, after 5s store value to EEPROM
    pixels.setBrightnessRelative(-BRIGHTNESS_OFFSET);
  }
  // Command : Decrease brightness
  else if (data == CHANGE_TO_RAINBOW)
  {
    if (programMgr.getCurrentProgram() == RAINBOW)
    {
      programMgr.setProgram(SET_MANUEL_COLOR);
      pixels.changeColor(myStore.getSavedColor(), true);
      pixels.loop();
    }
    else
    {
      programMgr.setProgram(RAINBOW);
    }
  }
  else
  {
    Serial.print("IR-Data : ");
    Serial.print(data, HEX);
    Serial.println("");
  }
}