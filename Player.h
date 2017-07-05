//Player drawing class

#ifndef PLAYER_H
#define PLAYER_H

#define SPRITE_SIZE 129
#define ANIMATION_DELAY 25
#define NUM_OF_FRAMES 20

//Include texture class
#include "Texture.h"

class Player{
public:
	//Constructor
	Player();

	//Render assignment method
	//Args:
	//SDL_Renderer* renderer - renderer to draw the sprites with
	void setRenderer(SDL_Renderer* renderer);
	
	//Rendering method
	//Args:
	//int x - X screen coordinate
	//int y - Y screen coordinate
	void render(int x, int y);

	//Resource releasing method
	void free();

	//Destructor
	~Player();

private:
	//Animation frame clipping rectangle
	SDL_Rect mAnimationFrame;

	//Current frame
	int miCurrentFrame;

	//Spritesheet texture
	Texture mSprite;

	//Animation timer
	Uint32 miAnimationTimer;
};

#endif
