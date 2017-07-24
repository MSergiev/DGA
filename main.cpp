//-----------------------------
//-----------INCLUDES----------
//-----------------------------


//Include local modules
#include "Game.h"
#include "SDL_Manager.h"


//-----------------------------
//----------VARIABLES----------
//-----------------------------


//Exit flag (from Shared.h)
bool quit = 0;

//SDL_Manager object
SDL_Manager manager;

//SDL event container
SDL_Event event;

//Game object
Game game;


//-----------------------------
//---------PROTOTYPES----------
//-----------------------------


//SDL initializing function
void init();

//Event handler
void eventHandler();


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
	init();

	//Game loop
	while(!quit){
		//Handle events
		eventHandler();

		//Loop game
		game.loop();

		//Render on screen
		SDL_RenderPresent(manager.getRenderer());
	}

#ifdef DEBUG
	cout << "Game loop broken" << endl;
#endif
    
    //Release sound
	Sound::free();

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
void init(){
	
#ifdef DEBUG
	cout << "Init called" << endl;
#endif

    Texture::mRenderer = manager.getRenderer();
    //Initialize sound
    Sound::load();
    //Initialize game event container
    game.setEvent(event);
    //Initialize game data
    game.init();
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
