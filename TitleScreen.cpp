/*
 * TitleScreen.cpp
 *
 *  Created on: Jul 17, 2017
 *      Author: Puzz
 */

#include "TitleScreen.h"

//empty constructor
TitleScreen::TitleScreen() {
	canContinue = 0;
}
//empty destructor
TitleScreen::~TitleScreen() {
	// TODO Auto-generated destructor stub
}

//Set continue flag
void TitleScreen::setContinue(bool canContinue){
	this->canContinue = canContinue;
}

//handles the event - > when a button is pressed to
//return the state of the button
int TitleScreen::eventHandler(SDL_Event& e) {
	int ButtonState=0;
	//if enough time has passed
	if(UI::debounce()){
		ButtonState|=StartButton.isClicked(e);
		ButtonState<<=1;
		ButtonState|=(ContinueButton.isClicked(e)&&canContinue);
		ButtonState<<=1;
		ButtonState|=QuitButton.isClicked(e);
	}
	return ButtonState;

}
//initializes the  buttons size and position
void TitleScreen::init() {
	loadBackground(TITLE_PATH);
	UI::loadFont(FONT_PATH,FONT_SIZE);

	StartButton.setTexture(START_PATH);
	ContinueButton.setTexture(CONTINUE_PATH);
	QuitButton.setTexture(QUIT_PATH);

	StartButton.setSize(BUTTON_WIDTH, BUTTON_HEIGHT);
	ContinueButton.setSize(BUTTON_WIDTH, BUTTON_HEIGHT);
	QuitButton.setSize(BUTTON_WIDTH, BUTTON_HEIGHT);

	StartButton.setSFX(BUTTON_SFX);
	ContinueButton.setSFX(BUTTON_SFX);
	QuitButton.setSFX(BUTTON_SFX);
	
	StartButton.setLocation((WIDTH-BUTTON_WIDTH)/2,HEIGHT-VERT_OFFSET-BUTTON_HEIGHT*5);
	ContinueButton.setLocation((WIDTH-BUTTON_WIDTH)/2,HEIGHT-VERT_OFFSET-BUTTON_HEIGHT*3);
	QuitButton.setLocation((WIDTH-BUTTON_WIDTH)/2,HEIGHT-VERT_OFFSET);
}
// render function that draws the image on the screen
void TitleScreen::render() {
	UI::render(); //calls the render method from the base class
	StartButton.render();
	if(canContinue) ContinueButton.render();
	QuitButton.render();
}
