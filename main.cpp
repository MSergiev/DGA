//-----------------------------
//----------CONSTANTS----------
//-----------------------------

//Screen constants
#define WIDTH 800
#define HEIGHT 800

//-----------------------------
//-----------INCLUDES----------
//-----------------------------

//Include SDL modules
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

//Include local modules
#include "Board.h"

//Misc library incluson
#include <iostream>
using std::cerr;
using std::endl;

//-----------------------------
//---------PROTOTYPES----------
//-----------------------------

//SDL initializing function
bool init();

//Event handler
void eventHandler();

//Resource freeing function
void free();

//-----------------------------
//----------VARIABLES----------
//-----------------------------

//SDL attributes
SDL_Window* window;
SDL_Renderer* renderer;

//Exit flag
bool quit = 0;

//SDL event container
SDL_Event event;

//Game board
Board board;




//-----------------------------
//------------MAIN-------------
//-----------------------------

int main(int argc, char* argv[]){
	//Unused warning elimination
	argc = 0; argv = 0;

	//Initialize SDL
	if(!init()) return 1;

	//Game loop
	while(!quit){
		//Handle events
		eventHandler();

		//Clear screen
		SDL_SetRenderDrawColor(renderer, 255,255,255,255);
		SDL_RenderClear(renderer);
	
		//Draw game board;
		board.render();
		
		//Render image on screen
		SDL_RenderPresent(renderer);
	}

	//Free resources
	free();

	//Successful exit
	return 0;
}




//-----------------------------
//----------FUNCTIONS----------
//-----------------------------

//SDL inititalizing function
bool init(){
	//Success flag
	bool success = 1;

	//Try to initialize SDL
	if(SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO)<0){
		cerr << "SDL Error: " << SDL_GetError() << endl;
		success = 0;
	} else {
		//Try to initialize SDL image
		if(!IMG_Init(IMG_INIT_PNG)){
			cerr << "IMG Error: " << IMG_GetError() << endl;
			success = 0;
		} else {
			//Try to initialize SDL mixer
			if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048)<0){
				cerr << "MIX Error: " << Mix_GetError() << endl;
				success = 0;
			} else {
				//Try to set linear filtering
				if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")){
					cerr << "- Linear filtering not enabled!" << endl;
				}
				//Create window
				window = SDL_CreateWindow("LUDO", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
				//Window integrity check
				if(window==NULL){
					cerr << "Window error: " << SDL_GetError() << endl;
					success = 0;
				} else {
					//Create renderer
					renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
					//Renderer integrity check
					if(renderer==NULL){
						cerr << "Renderer error: " << SDL_GetError() << endl;
						success = 0;
					} else {
						//Initialize game objects
						board.setRenderer(renderer);
						board.load();
					}
				}
			}
		}
	}

	//Return success flag
	return success;
}

//Event handler
void eventHandler(){
	while(SDL_PollEvent(&event)!=0){
		if(event.type == SDL_QUIT || event.key.keysym.sym == SDLK_ESCAPE)
			quit = 1;
	}
}


//Resource freeing function
void free(){
	//Release objects
	board.free();
	//Release renderer
	SDL_DestroyRenderer(renderer);
	//Release window
	SDL_DestroyWindow(window);
	//Quit functions
	Mix_Quit();
	IMG_Quit();
	SDL_Quit();
}
