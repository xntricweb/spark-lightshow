# LIGHTSHOW

The lightshow class wraps a neopixel and provides some basic effects. It is easy to customize and provides some basic effects for examples and starters.

## Usage

## quick start

```c++

// create the lightshow
LightShow lightshow(1);  // supply # of pixels

// create a transition
WheelTransition wheel(255);  // supply wheel resolution

// create a color picker
RainbowColorPicker rainbow();

void setup() {
    // initialize the lightshow
    lightshow.begin();

    // configure the lightshow with the chosen transition and color picker
    lightshow.useTransition(&wheel);
    lightshow.useColorPicker(&rainbow);
}

void loop() {
    // update the lightshow in the loop
    lightshow.update();
}

```

## lightshow object

Manages the lightshow state and effects.

### Lightshow::toColor / Lightshow::toRGB

Conversion functions for converting 3 pixel uint8 values to a single uint32 value, and vice versa.

```c++
uint8_t r = 0x80, g = 0xab, b = 0xfa;
uint32_t color;
LightShow::toColor(r, g, b, &color);  // color is now 0x0080abfa
color += 0x00010101;  // color is now 0x0081acfb
LightShow::toRGB(color, &r, &g, &b);  // r = 0x81, g = 0xac, b = 0xfb
color = toColor(r + 4, g - 2, b - 8); // color is 0x0085aaf3
```

### LightShow#constructor

Creates an instance of the lightshow, the constructor arguments are passed directly to the adafruit neopixel constructor.

```c++
#define PIXEL_COUNT 1
#define PIXEL_PORT D2
#define PIXEL_TYPE WS2812B
LightShow lightshow(PIXEL_COUNT, PIXEL_PORT, PIXEL_TYPE);
```

### LightShow#begin

Initializes a lightshow, typically would be called in the spark setup function.
Takes no arguments.

```c++
void setup(){
    lightshow.begin();
}
```

### LightShow#update

Updates the lightshow, typically called during the spark loop function.

```c++
LightShow lightshow(1);

void loop() {
    lightshow.update();
}
```

### LightShow#useTransition

Changes the transition driver currently used by the lightshow. There is
no default transition. Until one has been set, the lightshow will produce no output.

```c++
LightShow lightshow(1);
ImmediateTransition immediate;

void setup() {
    lightshow.useTransition(&immediate);
}
```

### LightShow#useColorPicker

Changes the color picker driver currently used by the lightshow and possibly
it's transition driver. Until the color picker driver has been set, there will
be no output.

```c++
LightShow lightshow(1);
SolidColorPicker solid;

void setup() {
    lightshow.useColorPicker(&solid);
}
```

### LightShow#getColorPicker

Typically this will be used by the transition driver to retrieve the current color picker.

```c++
LightShow lightshow(1);
SolidColorPicker solid;

void setup() {
    lightshow.useColorPicker(&solid);
    lightshow.getColorPicker(); // returns (ColorPicker \*) &solid
}
```

### LightShow#addColorFilter

Adds a color filter to the lightshow. Color filters are special objects that are used independent of the transition and color pickers. See below for more info.

```c++
LightShow lightshow(1);
BrightnessColorFilter brightness;

void setup() {
    lightshow.addColorFilter(brightness)
}
```

### LightShow#draw

Sets the color of a pixel to the specified color. The actual color applied will
vary depending on the filters in place. Draw will apply the filters to the
color after it has been called. Typically this function would be used by a
transition driver.

The neopixel will not be updated with the new information until a call to paint
is made.

```c++
lightshow.draw(1, 255, 0, 255)  // sets the first pixel to purple
```

### LightShow#paint

After all of the drawing has been completed a transition driver should call paint, to set the new pixel values to the neopixel.

```c++
lightshow.paint()  // updates the neopixel with the new pixel data
```

### LightShow#repeat

If repeat is called with true, the lightshow will repeat the transition after it has finished. Calling it with false disables the repeat feature.

```c++
lightshow.repeat(true);  // repeat enabled
lightshow.repeat(false);  // repeat disabled
```

### LightShow#applyFilters

This function is used internally by the lightshow to apply the filters after a color has been drawn... It is public in case a function would need to see what the result of filtering would look like for some reason.

```c++
uint8_t r = 255, g = 255, b = 255;
BrightnessColorFilter brightness;
brightness.set(128);
lightshow.addColorFilter(&brightness);
lightshow.applyFilters(&r, &g, &b);
// r = 128, g = 128, b = 128
```

### transitions

Transitions control the assignment of color from a color picker to a
pixel. Transitions must publicly inherit from the Transition interface.

#### Transition interface

provides an update function that will be called by the lightshow, the lightshow will call this function at a rate determined by the lightshow speed.

```c++

class Transition : public LightShowHelper {
public:
    virtual void reset();
    virtual void update() = 0;
protected:
    virtual void done();
};

```

```c++
```
