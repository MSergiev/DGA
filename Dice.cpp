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
(rand()%6)+1;
return 0;
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

bool Dice::init()
{
	//Initialization flag
		bool success = true;

		//Initialize SDL
		if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
		{
			printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create window
			gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
			if( gWindow == NULL )
			{
				printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Get window surface
				gScreenSurface = SDL_GetWindowSurface( gWindow );
			}
		}

		return success;
	}



void Dice::close() {
	//Deallocate surface
	SDL_FreeSurface( one );
	one = NULL;

	//Destroy window
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;

	//Quit SDL subsystems
	SDL_Quit();
}
