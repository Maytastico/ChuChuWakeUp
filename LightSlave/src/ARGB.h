#pragma once
#ifndef ARGB_H_
#define ARGB_H_

#include <Arduino.h>
#include <Rainbow.h>
#include <Adafruit_NeoPixel.h>
#include <EpromHandler.h>
#include <Timer.h>
#include <ProgramManager.h>

/** 
 * Is used to define how high the brightness value will be increased after pressing the corrosponding button
 * 
 */
const uint8_t BRIGHTNESS_OFFSET = 30;
/* 
 * Defines how many steps the brightness will be in- or decreased during an fade effect.
 */
const uint8_t BRIGHTNESS_STEP = 5;
/**
 * Defines the maximum brightness
 */
const uint8_t MAX_BRIGHTNESS = 255;
/**
 * Defines the minimum brightness
 */
const uint8_t MIN_BRIGHTNESS = 1;
/**
 * Defines how long it will take until the program checks whether the brightness has changed 
 */
const uint16_t STORING_DELAY_TIME = 1000 * 5; // 5s -> 5_000ms
const uint8_t DEFAULT_TIMER_DURATION = 50;

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

class ARGB : public Adafruit_NeoPixel
{
private:
  //Brightness Fade Constants
  uint8_t timerDuration = 30;

  EpromHandler *storage = nullptr;

  ProgramManager *program = nullptr;

  Program lastProgram;

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
   * Saves whether the Brightness has changed
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
   * Contains the state where the program for changing a color is in.
   */
  ChangeColor ChangeColorState = FADE_OUT;

  /* 
   * saves the current state of the stripes whether their on or off
   */
  bool isOnb = true;

  /* 
   * Turns the brightness of all rgbs to 0
   */
  void StripeOff();
  /* 
   * Turns the brightness of all rgbs to the saved brightness
   */
  void StripeOn();

  /* 
   * Executes the brightness state machine
   */
  void gotoBrightness(void);

  /* 
 * Executes the changeColor Statemachine
 */
  void changeToColor();

public:
  /**
   * Constructor for ARGB LEDS. It is in relation to the Adafruit Neopixel Liberay.
   * To easily access all functions to modify the attributes of the ARGB Stribe
   */
  ARGB(uint16_t numPixels, uint8_t ledPin, neoPixelType type) : Adafruit_NeoPixel(numPixels, ledPin, type)
  {
  }

  /**
   * Constructor for ARGB LEDS. It is in relation to the Adafruit Neopixel Liberay.
   * To easily access all functions to modify the attributes of the ARGB Stribe
   */
  ARGB(uint16_t numPixels, uint8_t ledPin, EpromHandler *rgbStorage, ProgramManager *programMgr, neoPixelType type) : Adafruit_NeoPixel(numPixels, ledPin, type)
  {
    storage = rgbStorage;
    program = programMgr;
  }

  /**
   * Fades a new color in
   * requires red , green and a value of b.
   * Values can be between 0 and 255
   */
  void changeColor(uint8_t r, uint8_t g, uint8_t b);
  /* 
   * Fades in a new color that takes a specific time
   * <Not implemented yet>
   */
  void changeColor(uint8_t r, uint8_t g, uint8_t b, uint16_t FadeDuration);
  /* 
   * Fades a new color in
   * requiers a 32 long integer
   */
  void changeColor(uint32_t color);

  void changeColor(uint32_t color, boolean forceFadeOut);
  /*
   * Returns the Current Brightness value to figure out what the next step of a program could be. 
   */
  uint8_t getBrightness(void);
  /* 
   * If the Stripe is on this function will turn it off
   * However is it on, it will turn it of
   */
  void toggleStripe();

  bool isStoringRequested(void);

  /* 
   * Executes all nessasary state machines that are requiered
   */
  void loop();
  /* 
   * Sets the storing request to false, when the current brightness was saved to EEPROM
   */
  void resetStoringRequest(void);
  /* 
   * Sets a brightness to all defined rgbs
   */
  void setBrightnes(uint8_t b);
  /* 
   * Increses the brightness of the stripe by a specified step
   */
  void setBrightnessRelative(int16_t step);
  /* 
   * Sets a 32 Bit formated color value
   */
  void setColor(uint32_t color);
  /* 
   * Sets a rgb defined color without animation 
   */
  void setColor(uint8_t r, uint8_t g, uint8_t b);
  /* 
   * Sets the target brightness to an value so the brightness state mashine will be triggert
   *  
   */
  void setTargetBrightness(uint8_t b);
  /**
   * Sets the last saved brightness value
   */
  void setTargetBrightness();
  /* 
   * Initilize the LED stripe with the saved values from the EEPROM
   */
  void setupARGB(uint8_t brightness, uint32_t color);
};

#endif // ARGB_H_