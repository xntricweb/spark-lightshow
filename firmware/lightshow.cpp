#include "lightshow.h"// This #include statement was automatically added by the Particle IDE.
#include "neopixel.h"

#define MIN_SPEED 0
#define MAX_FILTERS 10


LightShow::LightShow(uint16_t n, uint8_t p, uint8_t t)
: strip(n, p, t) {
    filter = (ColorFilter **) malloc(sizeof(ColorFilter *) * MAX_FILTERS);
}

LightShow::~LightShow() {
    free(filter);
}

uint32_t LightShow::toColor(uint8_t r, uint8_t g, uint8_t b) {
    uint32_t color = 0;
    toColor(r, g, b, &color);
    return color;
}

void LightShow::toColor(uint8_t r, uint8_t g, uint8_t b, uint32_t *color) {
    *color = ((uint32_t)r << 16) | ((uint32_t)g << 8) | (b);
}

void LightShow::toRGB(uint32_t color, uint8_t *r, uint8_t *g, uint8_t *b) {
    *r = color >> 16;
    *g = color >> 8;
    *b = color;
}

void LightShow::begin() {
    strip.begin();
}

void LightShow::update() {
    if(ready() && active && transition && picker) {
        bump_update();
        transition->update();
    }
}

void LightShow::useTransition(Transition *transition_) {
    transition = transition_;
    transition->lightshow = this;
    active = true;
}

void LightShow::useColorPicker(ColorPicker *picker_) {
    picker = picker_;
    picker->lightshow = this;
}

ColorPicker *LightShow::getColorPicker() {
    return picker;
}

void LightShow::addColorFilter(ColorFilter *filter_) {
    if(filter_count < MAX_FILTERS) {
        filter[filter_count++] = filter_;
        filter_->lightshow = this;
    } else {
        //TODO(xntricweb): should probably implement some kind of error handling in the future
    }
}

void LightShow::draw(uint16_t pixel, uint8_t r, uint8_t g, uint8_t b) {
    applyFilters(&r, &g, &b);
    strip.setPixelColor(pixel, r, g, b);
}

void LightShow::paint() {
    strip.show();
}

void LightShow::repeat(bool enabled) {
    repeat_ = enabled;
}

void LightShow::speed(uint8_t value) {
    speed_ = value < MIN_SPEED? MIN_SPEED : value;
}

void LightShow::transitionDone() {
    if(!repeat_)
        active = false;
}

uint16_t LightShow::pixelCount() {
    return strip.numPixels();
}

void LightShow::applyFilters(uint8_t *r, uint8_t *g, uint8_t *b) {
    for(size_t index = 0; index < filter_count; index++) {
        filter[index]->filter(r, g, b);
    }
}

bool LightShow::ready() {
    return millis() > next_update;
}

void LightShow::bump_update() {
    next_update = millis() + speed_;
}
