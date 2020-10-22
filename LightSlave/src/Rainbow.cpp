#include <Rainbow.h>

void Rainbow::setRainbow()
{
  for (unsigned int i = 0; i < p_argb->numPixels(); i++)
  { // For each pixel in strip...
    // Offset pixel hue by an amount to make one full revolution of the
    // color wheel (range of 65536) along the length of the strip
    // (strip.numPixels() steps):
    int pixelHue = firstHue + (i * 65536L / p_argb->numPixels());
    // strip.ColorHSV() can take 1 or 3 arguments: a hue (0 to 65535) or
    // optionally add saturation and value (brightness) (each 0 to 255).
    // Here we're using just the single-argument hue variant. The result
    // is passed through strip.gamma32() to provide 'truer' colors
    // before assigning to each pixel:
    p_argb->setPixelColor(i, p_argb->gamma32(p_argb->ColorHSV(pixelHue)));
  }
  p_argb->show();
}

void Rainbow::evaluateHue()
{
  firstHue += 256;
  if (firstHue > 5 * 65536)
  {
    firstHue = 0;
  }
}

void Rainbow::changeToRainbow()
{
  switch (this->animationState)
  {
  case FADE_OUT:
    this->p_argb->setTargetBrightness(MIN_BRIGHTNESS);
    if (this->p_argb->getBrightness() == MIN_BRIGHTNESS)
    {
      this->animationState = SET_FIRST;
      
    }
    break;
  case SET_FIRST:
    this->setRainbow();
    this->p_argb->setTargetBrightness();
    this->animationState = PLAY;
  break;
  case PLAY:
    this->setRainbow();
    this->evaluateHue();
    break;
  }
}

void Rainbow::start()
{
  this->animationState = FADE_OUT;
}
void Rainbow::stop()
{
  this->animationState = STBY;
}
void Rainbow::loop()
{
  if (this->animationState == STBY && p_program->getCurrentProgram() == RAINBOW)
    this->animationState = FADE_OUT;

  if (this->animationState != STBY)
  {
    if (refreshStripe.isTimerReady())
    {
      changeToRainbow();
      refreshStripe.startTimer(p_program->getUpdateRate());
    }
  }
}