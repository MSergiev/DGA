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
						}

						if (e.type == SDL_MOUSEBUTTONDOWN) {



					}

					}
				}
}

void Dice::init(){
srand(time(0));
	}



//void Dice::close() {
//	//Deallocate surface
//	SDL_FreeSurface( one );
//	one = NULL;
//
//	//Destroy window
//	SDL_DestroyWindow( gWindow );
//	gWindow = NULL;
//
//	//Quit SDL subsystems
//	SDL_Quit();
//}
