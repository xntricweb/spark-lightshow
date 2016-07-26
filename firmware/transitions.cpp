// Copyright 2016 Jeremy Calloway

#include "transitions.h"

void ImmediateTransition::update() {
    uint8_t r = 25, g = 25, b = 150;
    ColorPicker *picker = lightshow->getColorPicker();
    
    for (uint16_t i = 0, l = lightshow->pixelCount(); i < l; i++) {
        picker->select(i, l, &r, &g, &b);
        lightshow->draw(i, r, g, b);
    }
    
    lightshow->paint();
    
    lightshow->transitionDone();
}

void WipeTransition::update() {
    uint8_t r, g, b;
    
    lightshow->getColorPicker()
    ->select(
        pixel, 
        lightshow->pixelCount(), 
        &r, &g, &b);
        
    lightshow->draw(
        forward? pixel++: pixel--
        , r, g, b);
    
    lightshow->paint();
    
    if(pixel >= lightshow->pixelCount()) {
        lightshow->transitionDone();
        pixel = 0;
    }
}

void WipeTransition::setDirection(bool forward_) {
    forward = forward_;
}


WheelTransition::WheelTransition(uint16_t resolution_) {
    resolution = resolution_;
}

void WheelTransition::update() {
    uint8_t r = 25, g = 25, b = 150;
    ColorPicker *picker = lightshow->getColorPicker();
    
    for (uint16_t i = 0, l = lightshow->pixelCount(); i < l; i++) {
        picker->select(i + index++, resolution, &r, &g, &b);
        lightshow->draw(i, r, g, b);
    }
    
    lightshow->paint();
    
    if(index >= resolution) {
        index = 0;
        lightshow->transitionDone();
    }
}

void WheelTransition::setDirection(bool forward_) {
    forward = forward_;
}