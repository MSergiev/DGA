#ifndef SDL_MANAGER_H
#define SDL_MANAGER_H

///Include SDL modules
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

///Include basic library
#include <iostream>
using std::cout;
using std::cerr;
using std::endl;

///Include local modules
#include "Shared.h"

class SDL_Manager{

public:
	
	///Constructor
	SDL_Manager();

	///Renderer getter
	SDL_Renderer* getRenderer() const;

	///Destructor
	~SDL_Manager();

private:

	///SDL window object
	SDL_Window* mWindow;

	///SDL renderer object
	SDL_Renderer* mRenderer;
};

#endif
