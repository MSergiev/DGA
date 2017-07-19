/*
 * Dice.cpp
 *
 *  Created on: Jul 9, 2017
 *      Author: Puzz
 */
#include "Dice.h"
//empty constructor
Dice::Dice() {
}
//frees the  memory that the DiceTexture used
Dice::~Dice() {
	DiceTexture.free();
}
// method that draws the   dice texture on the screen
void Dice::setRenderer(SDL_Renderer* renderer){
if(renderer!=NULL){
		DiceTexture.setRenderer(renderer);
		DiceTexture.load(DICE_PATH);
}
}
//method that returns a random generated  number from 1 to 6
int Dice::roll() {
	DiceResult=(rand()%6)+1;
	return DiceResult;
}
//Flag to check if user has clicked inside the dice , and if so , rolls the dice.
bool Dice::Event(SDL_Event& e){
	bool hasClicked = 0;
	if (e.type == SDL_MOUSEBUTTONDOWN) {
		if( e.button.button == SDL_BUTTON_LEFT){
			int x,y;
			SDL_GetMouseState(&x,&y);
			if(x>=(WIDTH-DICE_WIDTH)/2 &&
				x<=(WIDTH+DICE_WIDTH)/2 &&
				y>=(HEIGHT-DICE_HEIGHT)/2 &&
				y<=(HEIGHT+DICE_HEIGHT)/2){
					Dice::roll();
					hasClicked = 1;
			}
		}
	}
	return hasClicked;
}
// sets  the image and the SIZE on the screen
void Dice::render(Colors c){
	SDL_Rect DiceFace={(DiceResult-1)*DICE_WIDTH,(c-1)*DICE_HEIGHT,DICE_WIDTH,DICE_HEIGHT};
	DiceTexture.render((WIDTH-DICE_WIDTH)/2,(HEIGHT-DICE_HEIGHT)/2,&DiceFace);
}
//method that sets the seed for the  random generator  from the current time
void Dice::init(){
srand(time(0));
	}

