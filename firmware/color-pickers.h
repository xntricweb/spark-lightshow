// Copyright 2016 Jeremy Calloway

#ifndef XWEB_LIGHTSHOW_COLOR_PICKERS_H_
#define XWEB_LIGHTSHOW_COLOR_PICKERS_H_

#include "lightshow.h"

class SolidColorPicker : public ColorPicker {
public:
    virtual void select(uint16_t index, uint16_t length, uint8_t *r, uint8_t *g, uint8_t *b);
    virtual void setColor(uint8_t r, uint8_t g, uint8_t b);
    virtual void setColor(uint32_t color);
private:
    uint8_t red, green, blue;
};

class RainbowColorPicker : public ColorPicker {
public:
    virtual void select(uint16_t index, uint16_t length, uint8_t *r, uint8_t *g, uint8_t *b);
};

class FadeColorPicker : public ColorPicker {
public:
    virtual void select(uint16_t index, uint16_t length, uint8_t *r, uint8_t *g, uint8_t *b);
    virtual void from(uint8_t r, uint8_t g,uint8_t b);
    virtual void to(uint8_t r, uint8_t g,uint8_t b);
protected:
    uint8_t fr=0, fg=0, fb=0, tr=255, tg=255, tb=255;
};

class FadeRandomColorPicker : public FadeColorPicker {
public:
    virtual void select(uint16_t index, uint16_t length, uint8_t *r, uint8_t *g, uint8_t *b);
};

#endif  // XWEB_LIGHTSHOW_COLOR_PICKERS_H_