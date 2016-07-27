#define PIXEL_COUNT 1
#define PIXEL_PORT D2
#define PIXEL_TYPE WS2812B
#define LIGHTSHOW_SPEED 45

#define LOCAL_IDE
// import the lightshow components
#ifndef LOCAL_IDE
#include "lightshow/lightshow.h"
#include "lightshow/transitions.h"
#include "lightshow/color-pickers.h"
#else
#include "lightshow.h"
#include "transitions.h"
#include "color-pickers.h"
#endif

// create the lightshow
LightShow lightshow(PIXEL_COUNT, PIXEL_PORT, PIXEL_TYPE);

// WheelTransition sets all of the pixels in one cycle, but shifts the pixels
// within a larger window. It's used to produce the rainbow effect from the
// neopixel examples
WheelTransition wheel(255);

// will supply rainbow colors to the transition
RainbowColorPicker rainbow;

void setup() {
    // setup the lightshow
    lightshow.begin();

    // set the transition speed of the lightshow
    lightshow.speed(LIGHTSHOW_SPEED);

    // set the transition driver
    lightshow.useTransition(&wheel);

    // set the color picker
    lightshow.useColorPicker(&rainbow);

    // tell the light show to repeat after the transition is done
    lightshow.repeat(true);
}

void loop() {
    // update the lightshow
    lightshow.update();
}
