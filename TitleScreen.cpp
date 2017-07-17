/*
 * TitleScreen.cpp
 *
 *  Created on: Jul 17, 2017
 *      Author: Puzz
 */

#include "TitleScreen.h"

TitleScreen::TitleScreen() {
	// TODO Auto-generated constructor stub

}

TitleScreen::~TitleScreen() {
	// TODO Auto-generated destructor stub
}

int TitleScreen::eventHandler(SDL_Event& e) {
	int ButtonState=0;
	ButtonState|=StartButton.isClicked(e);
	ButtonState<<=1;
	ButtonState|=ContinueButton.isClicked(e);
	ButtonState<<=1;
	ButtonState|=QuitButton.isClicked(e);
	return ButtonState;

}

void TitleScreen::init() {
	loadBackground(BOARD_PATH);
	UI::loadFont(FONT_PATH,12);

	StartButton.setRenderer(UI::getRenderer());
	StartButton.setLabel("START",UI::getFont(),SDL_Color {255,255,255,255});
	ContinueButton.setRenderer(UI::getRenderer());
	ContinueButton.setLabel("CONTINUE",UI::getFont(),SDL_Color {255,255,255,255});
	QuitButton.setRenderer(UI::getRenderer());
	QuitButton.setLabel("QUIT",UI::getFont(),SDL_Color {255,255,255,255});

	StartButton.setSize(200,30);
	StartButton.setLocation((WIDTH-200)/2,(HEIGHT+100)/2);
	ContinueButton.setSize(200,30);
	ContinueButton.setLocation((WIDTH-200)/2,(HEIGHT+200)/2);
	QuitButton.setSize(200,30);
	QuitButton.setLocation((WIDTH-200)/2,(HEIGHT+300)/2);
}

void TitleScreen::render() {
	UI::render();
	StartButton.render();
	ContinueButton.render();
	QuitButton.render();
}