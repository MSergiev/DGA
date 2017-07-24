/*
 * Dice.cpp
 *
 *  Created on: Jul 9, 2017
 *      Author: Puzz
 */
#include "Dice.h"
//empty constructor
Dice::Dice() {
	DiceTexture.load(DICE_PATH);
	DiceResult = 0;
}
//frees the  memory that the DiceTexture used
Dice::~Dice() {
	DiceTexture.free();
}
//method that sets dice position on screen
void Dice::setPosition(int x, int y){
	this->posX=x;
	this->posY=y;
}
//method that returns a random generated  number from 1 to 6
int Dice::roll() {
	DiceResult=(rand()%6)+1;
	return DiceResult;
}
//Dice roll setter
void Dice::setDiceResult(int DiceResult){
	this->DiceResult = DiceResult;
}
//Dice roll getter
int Dice::getDiceResult() const {
	return DiceResult;
}
//Flag to check if user has clicked inside the dice
bool Dice::Event(SDL_Event& e){
	if (e.type == SDL_MOUSEBUTTONDOWN) {
		if( e.button.button == SDL_BUTTON_LEFT){
			int x,y;
			SDL_GetMouseState(&x,&y);
			if(x>=posX && x<=posX+DICE_WIDTH &&
				y>=posY && y<=posY+DICE_HEIGHT){
					Dice::roll();
					return 1;
			}
		}
	}
	//if space is pressed
	if(e.key.keysym.sym == SDLK_SPACE)
		return 1;
	return 0;
}
// sets  the image and the SIZE on the screen
void Dice::render(){
	if(DiceResult!=0){
	SDL_Rect DiceFace={(DiceResult-1)*DICE_WIDTH,0,DICE_WIDTH,DICE_HEIGHT};
	DiceTexture.render(posX, posY, 1, &DiceFace);
	}
}
//method that sets the seed for the  random generator  from the current time
void Dice::init(){
srand(time(0));
	}
