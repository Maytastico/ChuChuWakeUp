#include <Arduino.h>

#ifndef _EEPROM_HANDLER_H_
#define _EEPROM_HANDLER_H_

const uint8_t DEF_BRIGHTNESS = 127;
const uint32_t DEF_COLOR = 255; // Blue
const uint8_t DEF_DEFAULTPROGRAM = 1;

class EpromHandler
{
private:
  struct ARGB_Data
  {
    uint8_t brightness;
    uint32_t color;
    uint8_t programStatus;
  };
  // loaded light data
  ARGB_Data actData;

public:
  EpromHandler(/* args */){};

  void begin();
  void getLightData(uint8_t *brightness, uint32_t *color, uint8_t *programmStatus) const;
  uint8_t getSavedBrightness();
  uint32_t getSavedColor();
  uint8_t getSavedProgram();

  void storeBrightness(uint8_t pBrightness);
  void storeColor(uint32_t pColor);
  void storeProgrammStatus(uint8_t pProgrammstatus);
};

#endif // _EEPROM_HANDLER_H_
