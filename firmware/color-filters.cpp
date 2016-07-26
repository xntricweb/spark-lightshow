// Copyright 2016 Jeremy Calloway

#include "color-filters.h"

// algorithm borrowed from neo_pixel.cpp, THANK YOU!
void BrightnessColorFilter::set(uint8_t value) {
    brightness = ++value;
}


void BrightnessColorFilter::filter(uint8_t *r, uint8_t *g, uint8_t *b) {
    if(brightness) {
        *r = (*r * brightness) >> 8;
        *g = (*g * brightness) >> 8;
        *b = (*b * brightness) >> 8;
    }
}

void NoiseColorFilter::setAmplitude(uint8_t value) {
    amplitude = value;
}

uint8_t NoiseColorFilter::addNoise(uint8_t c) {
    int16_t noise = c & 1? 
        c - random(amplitude):   
        c + random(amplitude);
    return 
      noise < 0? 0 
    : noise > 255? 255
    : noise;
}

void NoiseColorFilter::filter(uint8_t *r, uint8_t *g, uint8_t *b) {
    if(amplitude) {
        *r = addNoise(*r);
        *g = addNoise(*g);
        *b = addNoise(*b);
    }
}