#include "lightshow.h"// This #include statement was automatically added by the Particle IDE.
#include "neopixel.h"

#define MIN_SPEED 0
#define MAX_FILTERS 10

namespace xweb {

pixel_t red_pixel(rgb_t pixel) { return pixel >> 16; }
pixel_t green_pixel(rgb_t pixel) { return pixel >> 8; }
pixel_t blue_pixel(rgb_t pixel) { return pixel; }
rgb_t rgb(pixel_t r, pixel_t g, pixel_t b) {
   return (rgb_t)r << 16 | (rgb_t)g << 8 | b;
}

LightShow::LightShow(uint16_t n, uint8_t p, uint8_t t)
: strip(n, p, t) {
    filter = (ColorFilter **) malloc(sizeof(ColorFilter *) * MAX_FILTERS);
}

LightShow::~LightShow() {
    free(filter);
}

void LightShow::update() {
    if(ready() && transition && !transition->done && selector) {
        bump_update();
        transition->update();
        if(transition->done && repeat) {
            transition->reset();
        }
    }
}

void LightShow::setTransition(Transition &transition_) {
    transition = &transition_;
    transition.setLightShow(this);
    transition->reset();
}

Transition &LightShow::getTransition() {
    return *transition;
}

void LightShow::setColorSelector(ColorSelector &selector_) {
    selector = selector_;
}

ColorSelector &LightShow::getColorSelector() {
    return *selector;
}

void LightShow::addColorFilter(ColorFilter *filter_) {
    if(filter_count < MAX_FILTERS) {
        filter[filter_count++] = filter_;
        filter_->lightshow = this;
    } else {
        //TODO(xntricweb): should probably implement some kind of error handling in the future
    }
}

ColorFilter &getColorFilter(size_t index) {
    return *filter[index];
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

uint16_t LightShow::pixelCount() {
    return strip.numPixels();
}

void LightShow::applyFilters(uint8_t *r, uint8_t *g, uint8_t *b) {
    for(size_t index = 0; index < filter_count; index++) {
        filter[index]->filter(r, g, b);
    }
}

void LightShow::transition_done() {
    if(!repeat_)
        active = false;
}

bool LightShow::ready_for_update() {
    return millis() > next_update;
}

void LightShow::bump_update() {
    next_update = millis() + speed_;
}

LightShow &LightShowHelper::lightshow() {
    return *lightshow_;
}
void LightShowHelper::setLightShow(LightShow *lightshow) {
    lightshow_ = *lightshow;
}

}  // namespace xweb
