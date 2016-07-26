// This #include statement was automatically added by the Particle IDE.
#include "color-filters.h"

// This #include statement was automatically added by the Particle IDE.
#include "color-pickers.h"

// This #include statement was automatically added by the Particle IDE.
#include "transitions.h"

#define PIXEL_COUNT 1
#define PIXEL_PORT D2
#define PIXEL_TYPE WS2812B

// This #include statement was automatically added by the Particle IDE.
#include "blynk/blynk.h"

// This #include statement was automatically added by the Particle IDE.
#include "lightshow.h"
#include "transitions.h"
#include "color-pickers.h"
#include "color-filters.h"

char auth_token[] = "YOUR_AUTH_TOKEN_HERE";

LightShow lightshow(PIXEL_COUNT, PIXEL_PORT, PIXEL_TYPE);

BrightnessColorFilter brightness;
NoiseColorFilter noise;

ImmediateTransition immediate;
WheelTransition wheel(255);
WipeTransition wipe;

SolidColorPicker solid;
RainbowColorPicker rainbow;
FadeRandomColorPicker fade;

bool blynk_ready = false;

void setup() {
    lightshow.setup();
    lightshow.speed(100);
    // fade.from(255, 0, 255);
    // fade.to(0, 255, 0);
    
    lightshow.addColorFilter(&brightness);
    lightshow.addColorFilter(&noise);
    lightshow.useTransition(&wheel);
    lightshow.useColorPicker(&fade);
    lightshow.repeat(true);
}

void loop() {
    if(blynk_ready) {
        Blynk.run();
    } else if(Particle.connected()) {
        Blynk.begin(auth_token);
        blynk_ready = true;
    }
    lightshow.update();
}

BLYNK_WRITE(V1) {  // Mode
    int mode = param.asInt();
    if(mode == 1) {
        lightshow.repeat(true);
        lightshow.useTransition(&wheel);
        lightshow.useColorPicker(&rainbow);
    } else {
        lightshow.repeat(false);
        lightshow.useTransition(&wipe);
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

BLYNK_WRITE(V2) {  // Custom Color
    lightshow.useTransition(&wipe);
    lightshow.useColorPicker(&solid);
    solid.setColor(
        param[0].asInt() & 255,
        param[1].asInt() & 255,
        param[2].asInt() & 255
    );
}

BLYNK_WRITE(V3) {  // Brightnesss
    brightness.set(param.asInt() & 255);
}

BLYNK_WRITE(V4) {  // Speed
    lightshow.speed(param.asInt() & 255);
}

BLYNK_WRITE(V5) {  // Brightnesss
    noise.setAmplitude(param.asInt() & 255);
}