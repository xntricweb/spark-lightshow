// Copyright 2016 Jeremy Calloway

#ifndef XWEB_LIGHT_SHOW_COLOR_FILTER_H_
#define XWEB_LIGHT_SHOW_COLOR_FILTER_H_

#include "lightshow.h"

class BrightnessColorFilter : public ColorFilter {
public:
    virtual void filter(uint8_t *, uint8_t *, uint8_t *);
    virtual void set(uint8_t value);
private:
    uint8_t brightness = 128;
};

class NoiseColorFilter : public ColorFilter {
public:
    uint8_t addNoise(uint8_t c);
    virtual void filter(uint8_t *, uint8_t *, uint8_t *);
    virtual void setAmplitude(uint8_t value);
private:
    uint8_t amplitude = 0;
};

#endif  // XWEB_LIGHT_SHOW_COLOR_FILTER_H_