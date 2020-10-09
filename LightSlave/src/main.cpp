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

  serial.loop();
  if (serial.dataAvailable() == true)
  {
    processSerialCommand();
  }

} // end of loop

void processSerialCommand()
{
  serial.printOutSerialData();
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