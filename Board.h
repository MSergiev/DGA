//Game board drawing class

#ifndef BOARD_H
#define BOARD_H

//Include texture class
#include "Texture.h"
#include "Shared.h"

class Board{
public:
	//Constructor
	Board();

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
	//SDL board texture
	Texture mBoardTexture;
};

#endif
