// Copyright 2016 Jeremy Calloway

#include "color-pickers.h"

/* SOLID COLOR PICKER */

void SolidColorPicker::select(uint16_t index, uint16_t length, uint8_t *r, uint8_t *g, uint8_t *b) {
    *r = red;
    *g = green;
    *b = blue;
}

void SolidColorPicker::setColor(uint8_t r, uint8_t g, uint8_t b) {
    red = r;
    green = g;
    blue = b;
}

void SolidColorPicker::setColor(uint32_t color) {
    uint8_t r, g, b;
    LightShow::toRGB(color, &r, &g, &b);
    setColor(r, g, b);
}

/* RAINBOW COLOR PICKER */

void RainbowColorPicker::select(uint16_t index, uint16_t length, uint8_t *r, uint8_t *g, uint8_t *b) {
    uint8_t position = index * 255 / length;
    if(position < 43) {
        *r = 255;
        *g = position * 6;
        *b = 0;
    } else if(position < 86) {
        position -= 43;
        *r = 255 - position * 6;
        *g = 255;
        *b = 0;
    } else if(position < 128) {
        position -= 86;
        *r = 0;
        *g = 255;
        *b = position * 6;
    } else if(position < 171) {
        position -= 128;
        *r = 0;
        *g = 255 - position * 6;
        *b = 255;
    } else if(position < 214) {
        position -= 171;
        *r = position * 6;
        *g = 0;
        *b = 255;
    } else if(position < 256) {
        position -= 214;
        *r = 255;
        *g = 0;
        *b = 255 - position * 6;
    }
}

void FadeColorPicker::select(uint16_t index, uint16_t length, uint8_t *r, uint8_t *g, uint8_t *b) {
    *r = fr + (index * (tr - fr) / length);
    *g = fg + (index * (tg - fg) / length);
    *b = fb + (index * (tb - fb) / length);
}

void FadeColorPicker::from(uint8_t r, uint8_t g,uint8_t b) {
    fr = r;
    fg = g;
    fb = b;
}

void FadeColorPicker::to(uint8_t r, uint8_t g,uint8_t b) {
    tr = r;
    tg = g;
    tb = b;
}


void FadeRandomColorPicker::select(uint16_t index, uint16_t length, uint8_t *r, uint8_t *g, uint8_t *b) {
    if(index == length - 1) {
        fr = tr;
        fg = tg;
        fb = tb;
        tr = random(256);
        tg = random(256);
        tb = random(256);
    }
    FadeColorPicker::select(index, length, r, g, b);
}


