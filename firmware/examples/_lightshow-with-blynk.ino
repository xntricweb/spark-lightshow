#define PIXEL_COUNT 1
#define PIXEL_PORT D2
#define PIXEL_TYPE WS2812B


#define LOCAL_IDE

/**
 * UNCOMMENT THE FOLLOWING LINE AND UPDATE YOUR AUTH TOKEN TO
 * ENABLE BLYNK FEATURES.
 *
 * No blynk features will make it passed the preprocessor till the
 * the auth token is set to prevent build errors on the example.
*/

//#define BLYNK_AUTH_TOKEN "YOUR_AUTH_TOKEN_HERE"

#ifdef BLYNK_AUTH_TOKEN
#define BLYNK_WRAP(STUFF) STUFF
#else
#define BLYNK_WRAP(NO_STUFF)
#endif

BLYNK_WRAP(
#include "blynk/blynk.h"

char auth_token[] = BLYNK_AUTH_TOKEN;
bool blynk_ready = false;

// V1 is a blynk menu containing the following options in this order
// Rainbow
// White
// Red
// Green
// Blue
BLYNK_WRITE(V1) {  // Mode
    int mode = param.asInt();
    if(mode == 1) {  // rainbow selected
        // ensure repeat is enabled to keep the rainbow going
        lightshow.repeat(true);
        // set transition mode to wheel
        lightshow.useTransition(&wheel);
        // set color selector to rainbow
        lightshow.useColorPicker(&rainbow);
    } else {  // solid color selected
        // change repeat to false for solid colors, since setting it once is
        // enough
        lightshow.repeat(false);
        // set the transition to wipe
        lightshow.useTransition(&wipe);
        // set the color to a color based on the blynk selection
        lightshow.useColorPicker(&solid);
        solid.setColor(
            mode == 2? LightShow::toColor(255, 255, 255)  // White
        :   mode == 3? LightShow::toColor(255, 0, 0)  // Red
        :   mode == 4? LightShow::toColor(0, 255, 0)  // Green
        :   mode == 5? LightShow::toColor(0, 0, 255)  // Blue
        :   LightShow::toColor(0,0,0)
        );
    }
}

// V2 is a zeRGBA widget allowing custom color selection
BLYNK_WRITE(V2) {  // Custom Color
    lightshow.useTransition(&wipe);
    lightshow.useColorPicker(&solid);
    // sets the color to the selected mode
    solid.setColor(
        param[0].asInt() & 255,
        param[1].asInt() & 255,
        param[2].asInt() & 255
    );
}

// V3 is a brightness slider 0 - 255
BLYNK_WRITE(V3) {  // Brightnesss
    // set the brightness of the brightness filter
    brightness.set(param.asInt() & 255);
}

// V4 is a speed slider 255 - 0
BLYNK_WRITE(V4) {  // Speed
    // set the speed
    lightshow.speed(param.asInt() & 255);
}

// V5 is a noise slider 0 - 255
BLYNK_WRITE(V5) {  // Brightnesss
    noise.setAmplitude(param.asInt() & 255);
})

// import the lightshow components
#ifndef LOCAL_IDE
#include "lightshow/lightshow.h"
#include "lightshow/transitions.h"
#include "lightshow/color-pickers.h"
#include "lightshow/color-filters.h"
#else
#include "lightshow.h"
#include "transitions.h"
#include "color-pickers.h"
#include "color-filters.h"
#endif


// create the lightshow
LightShow lightshow(PIXEL_COUNT, PIXEL_PORT, PIXEL_TYPE);

// create some color filters
// allows control of the brightness
BrightnessColorFilter brightness;
// adds noise to the output color
NoiseColorFilter noise;

// create various transitions
// ImmediateTransition sets all of the pixels in one cycle
ImmediateTransition immediate;
// WheelTransition sets all of the pixels in one cycle, but shifts the pixels
// within a larger window. It's used to produce the rainbow effect from the
// neopixel examples
WheelTransition wheel(255);
// Sets one pixels color per cycle
WipeTransition wipe;

// create color pickers
// always supplies the specified color to the transition effect
// causes all of the pixels to be set to the same color
SolidColorPicker solid;
// will supply rainbow colors to the transition
RainbowColorPicker rainbow;
// will fade to a random color during the transition
FadeRandomColorPicker fade;

void setup() {
    // setup the lightshow
    lightshow.begin();

    // set the transition speed of the lightshow
    lightshow.speed(100);

    // add the color filters to the lightshow
    // filters are not required and may be left commented out
    lightshow.addColorFilter(&brightness);
    lightshow.addColorFilter(&noise);

    // set the initial transition driver
    lightshow.useTransition(&wheel);
    // set the initial color picker
    lightshow.useColorPicker(&fade);

    // tell the light show to repeat after the transition is done
    lightshow.repeat(true);
}

void loop() {
    BLYNK_WRAP(
    //run blynk, initialize if required
    if(blynk_ready) {
        Blynk.run();
    } else if(Particle.connected()) {
        Blynk.begin(auth_token);
        blynk_ready = true;
    })
    // update the lightshow
    lightshow.update();
}
