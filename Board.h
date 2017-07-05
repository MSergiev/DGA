//Game board drawing class

#ifndef BOARD_H
#define BOARD_H

//Include SDL modules
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

//Misc inclusions
#include <iostream>
using std::cerr;
using std::endl;
using std::string;

class Board{
public:
	//Constructor
	//Args:
	//SDL_Renderer* renderer - renderer to draw the board with
	Board(SDL_Renderer* renderer = NULL);

	//Board texture loading method
	void load();

	//Render assignment method
	//Args:
	//SDL_Renderer* renderer - renderer to draw the board with
	void setRenderer(SDL_Renderer* renderer);

	//Rendering method
	void render();

	//Resource releasing method
	void free();

	//Destructor
	~Board();

private:
	//SDL renderer pointer
	SDL_Renderer* mRenderer;

	//SDL board texture
	SDL_Texture* mBoardTexture;
};

#endif
