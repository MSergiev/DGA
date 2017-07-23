//-----------------------------
//-----------INCLUDES----------
//-----------------------------


//Include SDL modules
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

//Include local modules
#include "Game.h"


//-----------------------------
//----------VARIABLES----------
//-----------------------------


//SDL attributes
SDL_Window* window;
SDL_Renderer* renderer;

//Exit flag (from Shared.h)
bool quit = 0;

//SDL event container
SDL_Event event;

//Game object
Game game;


//-----------------------------
//---------PROTOTYPES----------
//-----------------------------


//SDL initializing function
bool init();

//Event handler
void eventHandler();

//Resource releasing function
void free();


//-----------------------------
//------------MAIN-------------
//-----------------------------


int main(int argc, char* argv[]){
#ifdef DEBUG
	cout << "========= DEBUG MODE =========" << endl;
#endif
	
	//Unused warning elimination
	argc = 0; argv = 0;

	//Initialize SDL
	if(!init()) return 1;

	//Game loop
	while(!quit){
		//Handle events
		eventHandler();

		//Loop game
		game.loop();

		//Render on screen
		SDL_RenderPresent(renderer);
	}

#ifdef DEBUG
	cout << "Game loop broken" << endl;
#endif

	//Free resources
	free();
#ifdef DEBUG
	cout << "========= SUCCESSFUL EXIT =========" << endl;
#endif
	//Successful exit
	return 0;
}


//-----------------------------
//----------FUNCTIONS----------
//-----------------------------


//SDL inititalizing function
bool init(){
	
#ifdef DEBUG
	cout << "Init called" << endl;
#endif
	
	//Success flag
	bool success = 1;

	//Try to initialize SDL_main
	if(SDL_Init(SDL_INIT_VIDEO)<0){
		cerr << "SDL Error: " << SDL_GetError() << endl;
		success = 0;
	} else {
	//Try to initialize SDL_image
	if(!IMG_Init(IMG_INIT_PNG)){
		cerr << "IMG Error: " << IMG_GetError() << endl;
		success = 0;
	} else {
	//Try to initialize SDL_mixer
	if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048)<0){
		cerr << "MIX Error: " << Mix_GetError() << endl;
		success = 0;
	} else {
	//Try to initialize SDL_ttf
	if(TTF_Init()==-1){
		cerr << "TTF Error: " << TTF_GetError() << endl;
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
				Texture::setRenderer(renderer);
                //Initialize sound
                Sound::load();
                //Initialize game
				game.setEvent(event);
                game.init();
				game.mRenderer = renderer;
			}
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
#ifdef DEBUG
	//cout << "EventHandler called" << endl;
#endif
	while(SDL_PollEvent(&event)!=0){
		//Application quit event
		if(event.type == SDL_QUIT || event.key.keysym.sym == SDLK_ESCAPE){
			quit = 1;
		}
		game.setEvent(event);
		game.eventHandler();
	}
}


//Resource freeing function
void free(){
#ifdef DEBUG
	cout << "Free called" << endl;
#endif

	//Release sound
	Sound::free();
	//Release renderer
	SDL_DestroyRenderer(renderer);
	//Release window
	SDL_DestroyWindow(window);
	//SDL Quit functions
	Mix_Quit();
	IMG_Quit();
	TTF_Quit();
	SDL_Quit();
}
