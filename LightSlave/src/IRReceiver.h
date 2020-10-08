#ifndef IRRECEIVER_H_
#define IRRECEIVER_H_

#include <Arduino.h>
#include <IRremote.h>


//IR Control Buttons
const long RED_COLOR = 16718565;
const long GREEN_COLOR = 16751205;
const long BLUE_COLOR = 16753245;
const long ORAGNE_COLOR = 0xFF2AD5;
const long LIME_COLOR = 0xFFAA55;
const long LIGHT_BLUE_COLOR = 0xFF926D;
const long WHITE = 0xFF22DD;
const long BRIGHT_UP = 0xFF3AC5;
const long BRIGHT_DOWN = 0xFFBA45;
const long CHANGE_TO_RAINBOW = 0xFFF00F;
const long TOGGLE_POWER = 0xFF02FD;
const long INCREASE_SPEED = 0xFFE817;
const long DEINCREASE_SPEED = 0xFFC837;

class IRReceiver
{
private:
  decode_results _results;
  uint32_t encodedData;
  bool dataFetched = false;
  IRrecv *_pIrRecv;

public:
  IRReceiver(IRrecv *irRecv);

  void begin();

  bool isDataFetched();

  bool isDataReady();

  uint32_t getEncodedData();
};

#endif // IRRECEIVER_H_