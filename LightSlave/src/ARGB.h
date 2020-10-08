#pragma once
#ifndef ARGB_H_
#define ARGB_H_

#include <Arduino.h>
#include <Rainbow.h>
#include <Adafruit_NeoPixel.h>
#include <EpromHandler.h>
#include <Timer.h>




const uint8_t BRIGHTNESS_OFFSET = 30;
const uint8_t BRIGHTNESS_STEP = 10;
const uint8_t MAX_BRIGHTNESS = 255;
const uint8_t MIN_BRIGHTNESS = 1;
const uint16_t STORING_DELAY_TIME = 1000 * 5; // 5s -> 5_000ms
const uint8_t TIMER_DURATION = 50;

class ARGB : public Adafruit_NeoPixel
{
private:
  
  uint8_t mosfetPin = 255;

  EpromHandler* storage = nullptr;

  /**
   * Timer for Fade in/out animation
   **/ 
  Timer timerBrightness;

  /**
   * Timer for storing brightness values to the
   * EEPROM
   */
  Timer timerStoring;

  Timer animationRefresh;

  /**
   * ?
   */
  bool bStoringRequest = false;

  /**
   * Will be set, if the brightness was changed by the user.
   */
  bool isBrighnessInChange = false;

  /**
   * Contains the brightness that was evaluated by the method
   * ARGB::setBrightnessRelative()
   */ 
  uint8_t currentBrightness = MAX_BRIGHTNESS;
  uint8_t targetBrightness = MAX_BRIGHTNESS;

  /**
   * Contains the brightness data befor the color will be changed
   */
  uint8_t oldBrightness;
  uint32_t currentColor;
  uint32_t targetColor;

  

  /**
   * Contains the certain states that program goes through when it
   * changes the color.
   */
  enum ChangeColor
  {
    STDBY,
    FADE_OUT,
    SET_COLOR,
    FADE_IN,
  };

  /**
   * Contains the state where the program for changing a color is in.
   */
  ChangeColor ChangeColorState = FADE_OUT;

  

  bool isOnb = true;

  void StripeOff();
  void StripeOn();

public:
  /**
   * Constructor for ARGB LEDS. It is in relation to the Adafruit Neopixel Liberay.
   * To easily access all functions to modify the attributes of the ARGB Stribe
   */
  ARGB(uint16_t numPixels, uint8_t ledPin, neoPixelType type) : Adafruit_NeoPixel(numPixels, ledPin, type) {
  }

  /**
   * Constructor for ARGB LEDS. It is in relation to the Adafruit Neopixel Liberay.
   * To easily access all functions to modify the attributes of the ARGB Stribe
   */
  ARGB(uint16_t numPixels, uint8_t ledPin, uint8_t mosfetPin, neoPixelType type) : Adafruit_NeoPixel(numPixels, ledPin, type) {
      this->mosfetPin = mosfetPin;
  }

  /**
   * Constructor for ARGB LEDS. It is in relation to the Adafruit Neopixel Liberay.
   * To easily access all functions to modify the attributes of the ARGB Stribe
   */
  ARGB(uint16_t numPixels, uint8_t ledPin, uint8_t mosfetPin, EpromHandler* rgbStorage, neoPixelType type) : Adafruit_NeoPixel(numPixels, ledPin, type) {
      this->mosfetPin = mosfetPin;
      storage = rgbStorage;
  }

  /**
   * Constructor for ARGB LEDS. It is in relation to the Adafruit Neopixel Liberay.
   * To easily access all functions to modify the attributes of the ARGB Stribe
   */
  ARGB(uint16_t numPixels, uint8_t ledPin, EpromHandler* rgbStorage, neoPixelType type) : Adafruit_NeoPixel(numPixels, ledPin, type) {
      storage = rgbStorage;
  }

  /**
   * 
   */
  void changeToColor();
  void changeColor(uint8_t r, uint8_t g, uint8_t b);
  void changeColor(uint32_t color);
  void changeColor(uint32_t color, boolean forceFadeOut);
  uint8_t getBrightness(void);
  void toggleStripe();
  void gotoBrightness(void);
  bool isStoringRequested(void);
  
  void loop();
  void resetStoringRequest(void);
  void setBrightnes(uint8_t b);
  void setBrightnessRelative(int16_t step);
  void setColor(uint32_t color);
  void setColor(uint8_t r, uint8_t g, uint8_t b);
  void setTargetBrightness(uint8_t b);
  void setupARGB(uint8_t brightness, uint32_t color);
};

#endif // ARGB_H_