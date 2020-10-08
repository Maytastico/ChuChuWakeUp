#include <EEPROM.h>
#include "EpromHandler.h"

void EpromHandler::begin(void)
{
  ARGB_Data storedData;

  // load data from EEPROM
  EEPROM.get(0, storedData);

  // EEPROM deleted ?
  if ((0 == storedData.brightness) || (0 == storedData.color))
  {
    // EEPROM deleted, write defaults
    storedData.brightness = DEF_BRIGHTNESS;
    storedData.color = DEF_COLOR;
    EEPROM.put(0, storedData);
  }
  // copy data from EEPROM
  this->actData = storedData;
}

// get loaded light data
void EpromHandler::getLightData(uint8_t *brightness, uint32_t *color) const
{
  *brightness = this->actData.brightness;
  *color = this->actData.color;
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
