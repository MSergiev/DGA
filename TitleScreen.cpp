/*
 * TitleScreen.cpp
 *
 *  Created on: Jul 17, 2017
 *      Author: Puzz
 */

#include "TitleScreen.h"

//empty constructor
TitleScreen::TitleScreen() {
	// TODO Auto-generated constructor stub
}
//empty destructor
TitleScreen::~TitleScreen() {
	// TODO Auto-generated destructor stub
}
//handles the event - > when a button is pressed to
//return the state of the button
int TitleScreen::eventHandler(SDL_Event& e) {
	int ButtonState=0;
	ButtonState|=StartButton.isClicked(e);
	ButtonState<<=1;
	ButtonState|=ContinueButton.isClicked(e);
	ButtonState<<=1;
	ButtonState|=QuitButton.isClicked(e);
	return ButtonState;

}
//initializes the  buttons size and position
void TitleScreen::init() {
	loadBackground(TITLE_PATH);
	UI::loadFont(FONT_PATH,FONT_SIZE);

	StartButton.setRenderer(UI::getRenderer());
	ContinueButton.setRenderer(UI::getRenderer());
	QuitButton.setRenderer(UI::getRenderer());
	
	StartButton.setLabel("START",UI::getFont(),SDL_Color C_WHITE);
	ContinueButton.setLabel("CONTINUE",UI::getFont(),SDL_Color C_WHITE);
	QuitButton.setLabel("QUIT",UI::getFont(),SDL_Color C_WHITE);

	StartButton.setSize(BUTTON_WIDTH, BUTTON_HEIGHT);
	ContinueButton.setSize(BUTTON_WIDTH, BUTTON_HEIGHT);
	QuitButton.setSize(BUTTON_WIDTH, BUTTON_HEIGHT);
	
	StartButton.setLocation((WIDTH-BUTTON_WIDTH)/2,HEIGHT-VERT_OFFSET-BUTTON_HEIGHT*5);
	ContinueButton.setLocation((WIDTH-BUTTON_WIDTH)/2,HEIGHT-VERT_OFFSET-BUTTON_HEIGHT*3);
	QuitButton.setLocation((WIDTH-BUTTON_WIDTH)/2,HEIGHT-VERT_OFFSET-BUTTON_HEIGHT);
}
// render function that draws the image on the screen
void TitleScreen::render() {
	UI::render(); //calls the render method from the base class
	StartButton.render();
	ContinueButton.render();
	QuitButton.render();
}
