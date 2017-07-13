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

//void Board::setRenderer(SDL_Renderer* renderer){
//	//Load texture
//	if(renderer!=NULL){
//		mBoardTexture.setRenderer(renderer);
//		mBoardTexture.load("./GFX/board.png");
//	}
//}
//
//void Board::render(){
//	//Draw board texture to screen
//	mBoardTexture.render(0,0);
//}
//
//void Board::free(){
//	//Release texture data
//	mBoardTexture.free();
//	mBoardTexture = NULL;
//}
