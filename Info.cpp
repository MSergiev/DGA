/*
 * Info.cpp
 *
 *  Created on: Jul 19, 2017
 *      Author: Puzz
 */

#include "Info.h"

Info::Info():NumberOfPages(2) {


}

Info::~Info() {
	// TODO Auto-generated destructor stub
}
//handles the event - > when a button is pressed to
//return the state of the button
int Info::eventHandler(SDL_Event& e) {
	int ButtonState=0;
	ButtonState=ButtonState | pageNext.isClicked(e);
	ButtonState=ButtonState | pageBack.isClicked(e);
	if(PageCounter<0){
		PageCounter=0;
				return 1;
	}
	else if(NumberOfPages>PageCounter){
		PageCounter=0;
		return 1;
	}
	else return 0;
}
//initializes the  buttons size and position
void Info::init() {

	pages[0].load(RULES_1_PATH);
	pages[0].setRenderer(UI::getRenderer());
	pages[1].load(RULES_2_PATH);
	pages[1].setRenderer(UI::getRenderer());


	pageNext.setRenderer(UI::getRenderer());
	pageBack.setRenderer(UI::getRenderer());
	pageNext.setSize(50,100);
	pageNext.setLocation((WIDTH-50),(HEIGHT-100)/2);
	pageBack.setSize(50,100);
	pageBack.setLocation((0),(HEIGHT-100)/2);
}
// render function that draws the image on the screen
//overwrite
void Info::render() {
	pages[PageCounter].render(0,0);
	//UI::render(); //calls the virtual render method from the base class UI
	//pageNext.render();
	//pageBack.render();
}
