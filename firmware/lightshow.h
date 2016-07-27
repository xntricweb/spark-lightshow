#ifndef XWEB_LIGHT_SHOW_H_
#define XWEB_LIGHT_SHOW_H_

#include "application.h"
#include "neopixel.h"

class Adafruit_NeoPixel;

namespace xweb {

class Transition;
class ColorSelector;
class ColorFilter;

typedef uint8_t pixel_t
typedef uint32_t rgb_t

pixel_t red_pixel(rgb_t pixel);
pixel_t green_pixel(rgb_t pixel);
pixel_t blue_pixel(rgb_t pixel);

rgb_t rgb(pixel_t r, pixel_t g, pixel_t b);

class LightShow {
public:
	LightShow(Adafruit_NeoPixel *strip_);
	~LightShow();

	void update();

	void setTransition(Transition &);
	Transition &getTransition();
	void setColorSelector(ColorSelector &);
	ColorSelector &getColorSelector();
	void addColorFilter(ColorFilter &);
	ColorFilter &getColorFilter(size_t index);

	void paint(uint16_t pixel, pixel_t r, pixel_t g, pixel_t b);
	void paint(uint16_t pixel, rgb_t color);

	void applyFilters(pixel_t &r, pixel_t &g, pixel_t &b);
	void show();

	void setRepeat(bool enabled);
	void setSpeed(uint8_t value);

	uint16_t pixelCount();

private:
	void transition_done();
	bool ready_for_update();
	void bump_update();

	Adafruit_NeoPixel *strip_;

	size_t filter_count;
	Transition *transition = NULL;
	ColorSelector *selector = NULL;
	ColorFilter **filter = NULL;

	bool repeat = false;
	bool active = true;
	uint8_t speed;
	uint64_t next_update = 0;
};

class LightShowHelper {
	friend class LightShow;
public:
	LightShow &lightshow();
private:
	void setLightShow(LightShow *);
	LightShow *lightshow_;
}

/**
 * A transition controls the effect cycle, the update method will be called
 * when it is time for the transition to produce the next "frame".
 */
class Transition : public LightShowHelper {
	friend class LightShow;
protected:

	/**
	 * Called by the lightshow when it is time to update the neopixel the
	 * frequency at which this is called is determined by the speed set on the
	 * lightshow.
	 */
	virtual void update() = 0;

	/**
	 * Transitions should call this method once the transition has completed.
	 * one cycle. If repeat is enabled on the lightshow, the cycle will restart
	 * automatically.
	 */
	virtual void finished() { done = true; }

	/**
	 * Called when/if a transition signals that it has finished.
	 */
	virtual void reset() { done = false; }

private:
	bool done = false;
};

class ColorSelector {
public:
	virtual void select(uint16_t i, uint16_t l, uint8_t &r, uint8_t &g, uint8_t &b) = 0;
};

class ColorFilter : public LightShowHelper {
public:
	virtual void filter(uint8_t *, uint8_t *, uint8_t *) = 0;
};

}  // namespace xweb

#endif  // XWEB_LIGHT_SHOW_H_
