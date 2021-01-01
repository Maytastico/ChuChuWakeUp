/**
 * @file StarLight.h
 * @author MacaroniDamage
 * @brief This effect should imitate a night sky
 * @version 0.1
 * @date 2020-12-23
 * 
 * 
 */
#ifndef _STARLIGHT_
#define _STARLIGHT_

#define AMOUNT_OF_STARS 20

#include <Arduino.h>
#include "Timer.h"
#include "LedController.h"
#include "TransitionHandler.h"

class StarLight
{
private:
    /**
 * @brief INIT generates the random positions of the stars
 *        CHOOSE choses a random star so the brightness of it will be changed
 *        LOOP changes the brightness of a star
 * 
 */
    enum StarLightStates
    {
        FIRST_DISPLAY,
        INIT,
        CHOOSE,
        LOOP,
    };

    StarLightStates stage = INIT;

    /**
     * @brief is used to refresh the state machine
     * 
     */
    Timer cycle;

    Timer firstINIT;

    /**
     * @brief A timer that specifies when a new star gets chosen
     * 
     */
    Timer chooseNewStar;

    /**
     * @brief Saves 10 star positions
     * 
     */
    uint8_t starPositions[AMOUNT_OF_STARS];
    /**
     * @brief Is used to modify the LEDs
     * 
     */
    LedController *_pController;

    /**
     * @brief Is to handle transitions
     * 
     */
    TransitionHandler *_pTransition;

    /**
     * @brief Temoprarily saves the brightness of a chosen star
     * 
     */
    uint8_t brightnessOfChosenStar = 255;

    /**
     * @brief Temoprarily saves the brightness of a chosen star
     * 
     */
    uint8_t targetBrightnessOfChosenStar = 32;
    /**
     * @brief Saves the index of the chosen star
     * 
     */
    uint8_t chosenStar;

    /**
     * @brief Generates random positions and saves them inside
     *        starPositions
     * 
     */
    void generateStarFrame();

    /**
     * @brief The state machine that handels init and brightness change
     * 
     */
    void starLightStage();

    /**
     * @brief Goes to the specified brightness
     * 
     */
    void gotoBrightness();

public:
    StarLight(){}

    /**
     * @brief Shows a white color an the defines positions
     * 
     */
    void displayStarFrame();

    /**
     * @brief Initializes the controller
     * 
     * @param controller 
     */
    void begin(LedController *controller)
    {
        _pController = controller;
    }

    void resetStateMachine();
    /**
     * @brief Executes the Statem machine after an cycle
     * 
     */
    void loop();
};

#endif //_STARLIGHT_