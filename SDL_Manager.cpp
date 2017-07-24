#include "SDL_Manager.h"

//SDL initializing constructor
SDL_Manager::SDL_Manager(){
    	
#ifdef DEBUG
		std::cout << "Init called" << endl;
#endif
	
	//Try to initialize SDL_main
	if(SDL_Init(SDL_INIT_VIDEO)<0){
		cerr << "SDL Error: " << SDL_GetError() << endl;
	} else {
	//Try to initialize SDL_image
	if(!IMG_Init(IMG_INIT_PNG)){
		cerr << "IMG Error: " << IMG_GetError() << endl;
	} else {
	//Try to initialize SDL_mixer
	if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048)<0){
		cerr << "MIX Error: " << Mix_GetError() << endl;
	} else {
	//Try to initialize SDL_ttf
	if(TTF_Init()==-1){
		cerr << "TTF Error: " << TTF_GetError() << endl;
	} else {
	//Try to set linear filtering
		if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")){
			cerr << "- Linear filtering not enabled!" << endl;
		}
		//Create window
		mWindow = SDL_CreateWindow("LUDO", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
		//Window integrity check
		if(mWindow==NULL){
			cerr << "Window error: " << SDL_GetError() << endl;
		} else {
			//Create renderer
			mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
			//Renderer integrity check
			if(mRenderer==NULL){
				cerr << "Renderer error: " << SDL_GetError() << endl;
            }
        }
	}
	}
	}
	}
}

//Get renderer
SDL_Renderer * SDL_Manager::getRenderer() const {
    return mRenderer;
}

//Release SDL data
SDL_Manager::~SDL_Manager(){
	//Release renderer
	SDL_DestroyRenderer(mRenderer);
	//Release window
	SDL_DestroyWindow(mWindow);
	//SDL Quit functions
	Mix_Quit();
	IMG_Quit();
	TTF_Quit();
	SDL_Quit();
}

