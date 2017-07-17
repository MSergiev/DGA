/*
 * Dice.cpp
 *
 *  Created on: Jul 9, 2017
 *      Author: Puzz
 */
#include "Dice.h"
Dice::Dice() {
}

Dice::~Dice() {
}

void Dice::setRenderer(SDL_Renderer* renderer){
if(renderer!=NULL){
		DiceTexture.setRenderer(renderer);
		DiceTexture.load(DICE_PATH);
}
}

int Dice::roll() {
	DiceResult=(rand()%6)+1;
	return DiceResult;
}

bool Dice::Event(SDL_Event& e){
	//Flag to check if user has clicked inside the dice
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

void Dice::render(Colors c){
	SDL_Rect DiceFace={(DiceResult-1)*DICE_WIDTH,(c-1)*DICE_HEIGHT,DICE_WIDTH,DICE_HEIGHT};
	DiceTexture.render((WIDTH-DICE_WIDTH)/2,(HEIGHT-DICE_HEIGHT)/2,&DiceFace);
}

void Dice::init(){
srand(time(0));
	}

