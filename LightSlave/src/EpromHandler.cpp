#include <EEPROM.h>
#include "EpromHandler.h"

void EpromHandler::begin(void)
{
  ARGB_Data storedData;

  // load data from EEPROM
  EEPROM.get(0, storedData);

  // EEPROM deleted ?
  if ((0 == storedData.brightness) || (0 == storedData.color) || (0 == storedData.programStatus))
  {
    // EEPROM deleted, write defaults
    storedData.brightness = DEF_BRIGHTNESS;
    storedData.color = DEF_COLOR;
    storedData.programStatus = DEF_DEFAULTPROGRAM;
    EEPROM.put(0, storedData);
  }
  // copy data from EEPROM
  this->actData.brightness = storedData.brightness;
  this->actData.color = storedData.color;
  this->actData.programStatus = storedData.programStatus;
}

// get loaded light data
void EpromHandler::getLightData(uint8_t *brightness, uint32_t *color, uint8_t *programmStatus) const
{
  *brightness = this->actData.brightness;
  *color = this->actData.color;
  *programmStatus = this->actData.programStatus;
}

// get loaded light data
uint32_t EpromHandler::getSavedColor()
{
  return this->actData.color;
}

// get loaded light data
uint8_t EpromHandler::getSavedBrightness()
{
  return this->actData.brightness;
}

uint8_t EpromHandler::getSavedProgram()
{
  return this->actData.programStatus;
}

// store brightness to EEPROM
void EpromHandler::storeBrightness(uint8_t pBrightness)
{
  this->actData.brightness = pBrightness;
  EEPROM.put(0, this->actData);
}

// store color to EEPROM
void EpromHandler::storeColor(uint32_t pColor)
{
  this->actData.color = pColor;
  EEPROM.put(0, this->actData);
}

// store color to EEPROM
void EpromHandler::storeProgrammStatus(uint8_t pProgrammstatus)
{
  this->actData.programStatus = pProgrammstatus;
  EEPROM.put(0, this->actData);
}