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
	if(pageNext.isClicked(e)) PageCounter++;
	else if(pageBack.isClicked(e)) PageCounter--;

	//if before first page
	if(PageCounter<0){
		PageCounter=0;
		return 1;
	}
	//if over last page
	else if(PageCounter>=PAGES_NUM){
		PageCounter=0;
		return 1;
	}
	else return 0;
}
//initializes the  buttons size and position
void Info::init() {
	//load page textures
	pages[0].load(RULES_1_PATH);
	pages[1].load(RULES_2_PATH);
	
	pageNext.setSize(RULES_WIDTH, RULES_HEIGHT);
	pageBack.setSize(RULES_WIDTH,RULES_HEIGHT);
	
	pageNext.setLocation((WIDTH-RULES_WIDTH),(HEIGHT-RULES_HEIGHT)/2);
	pageBack.setLocation(0,(HEIGHT-RULES_HEIGHT)/2);
	
//	UI::loadBackground(RULES_1_PATH);
}
// render function that draws the image on the screen
//overwrite
void Info::render() {
	pages[PageCounter].render(0,0);
	
	//UI::render(); //calls the virtual render method from the base class UI
	//pageNext.render();
	//pageBack.render();
}