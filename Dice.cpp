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
Texture::setRenderer(SDL_Renderer* renderer){
if(renderer!=NULL){
		DiceTexture.setRenderer(renderer);
		DiceTexture.load("./GFX/Dice/DiceSides.png");
}
}
void cropAllDiceSides() {
	SDL_Rect tempRect = { 0, 0, DICE_WIDTH, DICE_HEIGHT };
	for (int i = 0; i < 6; i++) {
		tempRect.x = 0;
		for (int j = 0; j < 6; j++) {
			sides.push_back(tempRect);
			tempRect.x += DICE_WIDTH;
		}
		tempRect.y += DICE_HEIGHT;
	}
}
void setAllSides() {
}

int Dice::roll() {
return (rand()%6)+1;
 }

void Dice::Event(){
		//Event handler
				bool quit = false;
				SDL_Event e;
				//While application is running
				while (!quit) {
					//Handle events on queue
					while (SDL_PollEvent(&e) != 0) {
						//User requests quit
						if (e.type == SDL_QUIT) {
							quit = true;
						} //end if
						if (e.type == SDL_MOUSEBUTTONDOWN) {
							switch( e.button.button == SDL_BUTTON_LEFT)
							{
							case SDL_MOUSEBUTTONDOWN:
								Dice::roll();
								break;

					} //end  switch
					}//end second if
				} // end  while
					//SDL_RenderPresent(gRenderer);
}// end of while
}//end of function

void Dice::init(){
srand(time(0));
	}

