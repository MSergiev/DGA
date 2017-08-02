//Slider class

#ifndef SLIDER_H
#define SLIDER_H

#include "Texture.h"
#include "Sound.h"

class Slider {

public:

	///Constructor
	///Args:
	///int x - top left X coordinate (not required)
	///int y - top left Y coordinate (not required)
	///int w - slider base width (not required)
	///int h - slider base height (not required)
	Slider(int x = 0, int y = 0, int w = 10, int h = 10);

	///Assign base texture
	///Args:
	///string texturePath - path to texture
	void setBaseTexture(string texturePath);

	///Assign knob texture
	///Args:
	///string texturePath - path to texture
	void setKnobTexture(string texturePath);

	///Size setter
	///Args:
	///int w - slider width
	///int h - slider height
	void setSize(int w, int h);

	///Location setter
	///Args:
	///int x - top left X coordinate
	///int y - top left Y coordinate
	void setLocation(int x, int y);

	///Slider range setter
	///Args:
	///int from - from
	///int to - to
	void setRange(int from, int to);

	///Get slider value
	float getSliderValue() const;

	///Event handler
	///Args:
	///SDL_Event& e - reference to SDL_Event instance
	bool eventHandler(SDL_Event& e);

	///Get slider value mapped to range
	///Args:
	///float from - range start
	///float to - range end
	float mapFromSlider(float from, float to);
	
	///Render method
	void render();

	///Destructor
	~Slider();

private:

	///Get value mapped to slider range
	///Args:
	///int from - range start
	///int to - range end
	///int val - value to be mapped
	float mapToSlider(int from, int to, int val);

	///Slider base texture
	Texture mSliderBase;

	///Slider knob texture
	Texture mSliderKnob;

	///Slider size
	SDL_Rect mSize;

	///Slider position
	float mfPosition;

	///Slider range
	SDL_Rect mRange;
};

#endif
