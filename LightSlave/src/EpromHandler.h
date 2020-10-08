#include <Arduino.h>

#ifndef _EEPROM_HANDLER_H_
#define _EEPROM_HANDLER_H_

const uint8_t DEF_BRIGHTNESS = 127;
const uint32_t DEF_COLOR = 255; // Blue

struct ARGB_Data
{
  uint8_t brightness;
  uint32_t color;
};

class EpromHandler
{
private:
  // loaded light data
  ARGB_Data actData;

public:
  EpromHandler(/* args */){};

  void begin();
  void getLightData(uint8_t *brightness, uint32_t *color) const;
  uint8_t getSavedBrightness();
  uint32_t getSavedColor();

  void storeBrightness(uint8_t pBrightness);
  void storeColor(uint32_t pColor);
};

#endif // _EEPROM_HANDLER_H_
