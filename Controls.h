#ifndef Controls_H
#define CONTROLS_H

#include "UI.h"

class Controls: public UI {

public:

	//Constructor
	Controls();

	//UI initializing method
	void init();

	//Event handler
	//Args:
	//SDL_Event& e - reference to SDL event container
	virtual int eventHandler(SDL_Event& e);

	//Render method
	virtual void render();

	//Destructor
	virtual ~Controls();

private:
	
	//Sound state
	bool mbSoundState = 1;

	//Button objects
	Button mSoundButton;
	Button mRulesButton;
	Button mQuitButton;
};

#endif
