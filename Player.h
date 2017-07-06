//Player class

#ifndef PLAYER_H
#define PLAYER_H

#define SPRITE_SIZE 129
#define ANIMATION_DELAY 25
#define NUM_OF_FRAMES 20

//Include sprite class
#include "Sprite.h"

class Player{
public:
	//Constructor
	Player();

	//Rendering method
	//Args:
	//int x - X screen coordinate
	//int y - Y screen coordinate
	void render(int x, int y);

	//Set renderer
	//Args:
	//SDL_Renderer* renderer - renderer to draw the sprites with
	void setRenderer(SDL_Renderer* renderer);

	//Destructor
	~Player();

private:

	//Sprite object pointer
	Sprite* mPlayerSprite;
};

#endif
