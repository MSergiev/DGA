/*
 * Info.cpp
 *
 *  Created on: Jul 19, 2017
 *      Author: Puzz
 */

#include "Info.h"

Info::Info() {
PageCounter = 0;
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
		bool nextState = pageNext.isClicked(e);
		bool backState = pageBack.isClicked(e);
		if(nextState) PageCounter++;
		else if(backState) PageCounter--;
		ButtonState|=(backState&&PageCounter==0);
		ButtonState<<=1;
		ButtonState|=(nextState&&PageCounter==0);
		ButtonState<<=1;
		ButtonState|=(backState&&PageCounter==1);
		ButtonState<<=1;
		ButtonState|=(nextState&&PageCounter==1);
		ButtonState<<=1;
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
	//load page textures
	pages[0].load(RULES_1_PATH);
	pages[1].load(RULES_2_PATH);
	
	pageNext.setSize(RULES_WIDTH, RULES_HEIGHT);
	pageBack.setSize(RULES_WIDTH,RULES_HEIGHT);

	pageNext.setSFX(BUTTON_SFX);
	pageBack.setSFX(BUTTON_SFX);

	pageNext.setLocation((WIDTH-RULES_WIDTH),(HEIGHT-RULES_HEIGHT)/2);
	pageBack.setLocation(0,(HEIGHT-RULES_HEIGHT)/2);
	
//	UI::loadBackground(RULES_1_PATH);
}
// render function that draws the image on the screen
//overwrite
void Info::render() {
	//pages[PageCounter].render(0,0);
}
