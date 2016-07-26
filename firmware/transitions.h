//Copyright 2016 Jeremy Calloway

#ifndef XWEB_LIGHTSHOW_TRANSITIONS_H_
#define XWEB_LIGHTSHOW_TRANSITIONS_H_

#include "lightshow.h"

class ImmediateTransition : public Transition {
    virtual void update();
};

class WipeTransition : public Transition {
public:
    virtual void update();
    virtual void setDirection(bool forward);
private:
    bool forward = true;
    uint16_t pixel = 0;
};

class WheelTransition : public Transition {
public:
    WheelTransition(uint16_t);
    virtual void update();
    virtual void setDirection(bool forward);
    
private:
    bool forward = true;
    uint16_t index = 0;
    uint16_t resolution = 255;
};

#endif  // XWEB_LIGHTSHOW_TRANSITIONS_H_