/*
 * Info.cpp
 *
 *  Created on: Jul 19, 2017
 *      Author: Puzz
 */

#include "Info.h"

Info::Info() {
}

Info::~Info() {
	// TODO Auto-generated destructor stub
}

//handles the event - > when a button is pressed to
//return the state of the button
int Info::eventHandler(SDL_Event& e) {
	int ButtonState = 0;
	//event timer
	if(UI::debounce()){
		ButtonState|=(pageNext.isClicked(e));
		ButtonState<<=1;
		ButtonState|=(pageBack.isClicked(e));
	}
	return ButtonState;
}
//overridden fade effects
void Info::fadeIn(){
	pageNext.fadeIn(FADE_FACTOR);
	pageBack.fadeIn(FADE_FACTOR);
}
void Info::fadeOut(){
	pageNext.fadeOut(FADE_FACTOR);
	pageBack.fadeOut(FADE_FACTOR);
}
//initializes the  buttons size and position
void Info::init() {
	pageNext.setSize(RULES_WIDTH, RULES_HEIGHT);
	pageBack.setSize(RULES_WIDTH,RULES_HEIGHT);

	pageNext.setSFX(BUTTON_SFX);
	pageBack.setSFX(BUTTON_SFX);

	pageNext.setLocation((WIDTH-RULES_WIDTH),(HEIGHT-RULES_HEIGHT)/2);
	pageBack.setLocation(0,(HEIGHT-RULES_HEIGHT)/2);
	
}
// render function that draws the image on the screen
//override
void Info::render() {
}
