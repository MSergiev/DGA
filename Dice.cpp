/*
 * Dice.cpp
 *
 *  Created on: Jul 9, 2017
 *      Author: Puzz
 */
#include "Dice.h"
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
SDL_Window* gWindow = NULL;
SDL_Surface* gScreenSurface = NULL;
Dice::Dice() {
}
Dice::~Dice() {
}

void Dice::roll() {
	srand((unsigned)time(0));
		    int face;
		    face = (rand()%6)+1;
	      switch ( face )
	      {
	      case 1:
	   	          cout<<"1"<<endl;
	   	            break;
	   	         case 2:
	   	        	 cout<<"2"<<endl;
	   	            break;
	   	         case 3:
	   	        	 cout<<"3"<<endl;
	   	            break;
	   	         case 4:
	   	        	 cout<<"4"<<endl;
	   	            break;
	   	         case 5:
	   	        	 cout<<"5"<<endl;
	   	            break;
	   	         case 6:
	   	        	 cout<<"6"<<endl;
	   	            break;
	      }
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


bool Dice::loadMedia() {
	//Loading success flag
	bool success = true;

	//Load splash image
	one = SDL_LoadBMP( "11.bmp" );
	if( one == NULL )
	{
		printf( "Unable to load image %s! SDL Error: %s\n", "x.bmp", SDL_GetError() );
		success = false;
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
