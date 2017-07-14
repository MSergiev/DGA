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
		DiceTexture.load("Dice.png");
}
}

int Dice::roll() {
	DiceResult=(rand()%6)+1;
return DiceResult;
 }

void Dice::Event(SDL_Event& e){
	if (e.type == SDL_MOUSEBUTTONDOWN) {
		if( e.button.button == SDL_BUTTON_LEFT){
			int x,y;
				SDL_GetMouseState(&x,&y);
				if(x>=(WIDTH-DICE_WIDTH)/2 &&
					x<=(WIDTH+DICE_WIDTH)/2 &&
					y>=(HEIGHT-DICE_HEIGHT)/2 &&
					y<=(HEIGHT+DICE_HEIGHT)/2){
					Dice::roll();
				}

} //end  switch
}//end second if
} // end  while
void Dice::render() {
	SDL_Rect DiceFace={(DiceResult-1)*DICE_WIDTH,0,DICE_WIDTH,DICE_HEIGHT};
	DiceTexture.render((WIDTH-DICE_WIDTH)/2,(HEIGHT-DICE_HEIGHT)/2,&DiceFace);
}

void Dice::init(){
srand(time(0));
	}

