#include "StarLight.h"

void StarLight::generateStarFrame()
{
    Serial.println("Generating Random positions");
    for (unsigned int i = 0; i < AMOUNT_OF_STARS; i++)
    {

        //sets a random color to every pixel
        uint8_t pos = _pController->generateRadomPosition();
        this->starPositions[i] = pos;
        //Serial.println("index: " + String(i) + " pos: " + String(pos));
    }
}

void StarLight::displayStarFrame()
{
    for (unsigned int i = 0; i < AMOUNT_OF_STARS; i++)
    {
        //sets a random color to every pixel
        uint8_t pos = _pController->generateRadomPosition();
        uint8_t intensity = random(64, 255);
        this->starPositions[i] = pos;

        
         switch (_pController->getLedMode())
        {
        case RGB:
            _pController->setPixelColor(starPositions[i], _pController->Color(intensity, intensity, intensity));
             break;
        case RGBW:
            _pController->setPixelColor(starPositions[i], _pController->Color(0, 0, 0, intensity));
            break; 
        }
    }
    _pController->show();
}

void StarLight::starLightStage()
{
    switch (stage)
    {
    case FIRST_DISPLAY:
        if (firstINIT.isTimerReady())
        {
            displayStarFrame();
            stage = CHOOSE;
        }
        break;
    case INIT:
        generateStarFrame();
        stage = FIRST_DISPLAY;
        firstINIT.startTimer(1000);
        break;
    case CHOOSE:
        chosenStar = random(0, AMOUNT_OF_STARS);
        //Serial.println("Star chosen: " + String(chosenStar));
        stage = LOOP;
        chooseNewStar.startTimer(60000);
        break;

    case LOOP:
        gotoBrightness();
        if (brightnessOfChosenStar <= 32)
        {
            targetBrightnessOfChosenStar = 255;
        }
        else if (brightnessOfChosenStar >= 255)
        {
            targetBrightnessOfChosenStar = 32;
        }

        if (chooseNewStar.isTimerReady())
        {
            stage = CHOOSE;
        }
        //Serial.println("Brightness of star: " + String(brightnessOfChosenStar));

        break;
    }
}

// change to a target brightness
void StarLight::gotoBrightness()
{
    int16_t actBrightness = (int16_t)brightnessOfChosenStar;
    if (targetBrightnessOfChosenStar > brightnessOfChosenStar)
    {
        actBrightness += BRIGHTNESS_STEP;
        if (actBrightness > targetBrightnessOfChosenStar)
            brightnessOfChosenStar = targetBrightnessOfChosenStar;
        else
            brightnessOfChosenStar = actBrightness;
    }
    else if (targetBrightnessOfChosenStar < brightnessOfChosenStar)
    {
        actBrightness -= BRIGHTNESS_STEP;
        if (actBrightness < targetBrightnessOfChosenStar)
            brightnessOfChosenStar = targetBrightnessOfChosenStar;
        else
            brightnessOfChosenStar = (uint8_t)actBrightness;
    }
    //Refreshes the stripe
    switch (_pController->getLedMode())
    {
    case RGB:
        _pController->setPixelColor(starPositions[chosenStar], _pController->Color(brightnessOfChosenStar, brightnessOfChosenStar, brightnessOfChosenStar));
        break;
    case RGBW:
        _pController->setPixelColor(starPositions[chosenStar], _pController->Color(0, 0, 0, brightnessOfChosenStar));
        break;
    }

    _pController->show();
}

void StarLight::resetStateMachine()
{
    stage = INIT;
}

void StarLight::loop()
{
    if (cycle.isTimerReady())
    {
        starLightStage();
        cycle.startTimer(100);
    }
}