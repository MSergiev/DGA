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
		DiceTexture.load("./GFX/Dice/Dice.png");
}
}

int Dice::roll() {
	DiceResult=(rand()%6)+1;
return DiceResult;
 }

//void Dice::Event(){
//		//Event handler
//				bool quit = false;
//				SDL_Event e;
//				//While application is running
//				while (!quit) {
//					//Handle events on queue
//					while (SDL_PollEvent(&e) != 0) {
//						//User requests quit
//						if (e.type == SDL_QUIT) {
//							quit = true;
//						} //end if
//						if (e.type == SDL_MOUSEBUTTONDOWN) {
//							switch( e.button.button == SDL_BUTTON_LEFT)
//							{
//							case SDL_MOUSEBUTTONDOWN:
//								Dice::roll();
//								break;
//
//					} //end  switch
//					}//end second if
//				} // end  while
//					//SDL_RenderPresent(gRenderer);
//}// end of while
//}//end of function

void Dice::render() {
	SDL_Rect DiceFace={(DiceResult-1)*DICE_WIDTH,0,DICE_WIDTH,DICE_HEIGHT};
DiceTexture.render((WIDTH-DICE_WIDTH)/2,(WIDTH-DICE_WIDTH)/2,&DiceFace);
}

void Dice::init(){
srand(time(0));
	}

