#ifndef VOLUME_H
#define VOLUME_H

#include "UI.h"
#include "Slider.h"

class Volume: public UI {

public:

	///Constructor
	Volume();

	///UI initializing method
	void init();

	///Event handler
	///Args:
	///SDL_Event& e - reference to SDL event container
	virtual int eventHandler(SDL_Event& e);

	///Render method
	virtual void render();

	///Sliders fade in
	virtual void fadeIn();

	///Sliders fade out
	virtual void fadeOut();

	///Destructor
	virtual ~Volume();

private:
	
	///Slider objects
	Slider mSFX, mBGM;
};

#endif
