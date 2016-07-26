#ifndef XWEB_LIGHT_SHOW_H_
#define XWEB_LIGHT_SHOW_H_

#include "application.h"
#include "neopixel.h"

class LightShow;

/**
 * Provides helpers access to the current lightshow, the lightshow value is set
 * by the lightshow when it is added to it. This value should not be changed by
 * the users program.
 */
class LightShowHelper {
	friend class LightShow;
protected:
	LightShow *lightshow = NULL;
};

/**
 * A transition controls the effect cycle, the update method will be called
 * when it is time for the transition to produce the next "frame".
 */
class Transition : public LightShowHelper {
public:
	/**
	 * Called when/if a transition signals that it has finished.
	 */
	virtual void reset() { }

	/**
	 * Called by the lightshow when it is time to update the neopixel the
	 * frequency at which this is called is determined by the speed set on the
	 * lightshow.
	 */
	virtual void update() = 0;
protected:

	/**
	 * Transitions should call this method once the transition has completed.
	 * one cycle. If repeat is enabled on the lightshow, the cycle will restart
	 * automatically.
	 */
	virtual void done() {
		lightshow->transitionDone();
		reset();
	}
};

class ColorPicker : public LightShowHelper {
public:
	virtual void select(uint16_t i, uint16_t l, uint8_t *r, uint8_t *g, uint8_t *b) = 0;
};

class ColorFilter : public LightShowHelper {
public:
	virtual void filter(uint8_t *, uint8_t *, uint8_t *) = 0;
};

class LightShow {
public:
	LightShow(uint16_t n, uint8_t p=2, uint8_t t=WS2812B);
	~LightShow();
	static void toColor(uint8_t r, uint8_t g, uint8_t b, uint32_t *color);
	static uint32_t toColor(uint8_t r, uint8_t g, uint8_t b);
	static void toRGB(uint32_t color, uint8_t *r, uint8_t *g, uint8_t *b);

	void begin();
	void update();

	void useTransition(Transition *transition_);
	void useColorPicker(ColorPicker *picker_);
	ColorPicker *getColorPicker();
	void addColorFilter(ColorFilter *filter_);

	void draw(uint16_t pixel, uint8_t r, uint8_t g, uint8_t b);
	void paint();

	void repeat(bool enabled);
	void applyFilters(uint8_t *r, uint8_t *g, uint8_t *b);

	void speed(uint8_t value);
	void transitionDone();
	uint16_t pixelCount();

private:
	bool ready();
	void bump_update();
	Adafruit_NeoPixel strip;

	Transition *transition = NULL;
	ColorPicker *picker = NULL;

	size_t filter_count;
	ColorFilter **filter = NULL;

	bool repeat_ = false;
	bool active = true;
	uint8_t speed_;
	uint64_t next_update = 0;
};

#endif  // XWEB_LIGHT_SHOW_H_
