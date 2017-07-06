//Sprite drawing class

#ifndef SPRITE_H
#define SPRITE_H

//Include inheritance base class
#include "Texture.h"

class Sprite : public Texture{
public:
	
	//Constructor
	//Args:
	//SDL_Rect frameSize - size and location of first frame
	//(*)Uint32 numOfFrames - number of frames
	//(*)Uint32 animationDelay - animation delay (in ms)
	Sprite(SDL_Rect animationFrame, 
			Uint32 numOfFrames = 1, Uint32 animationDelay = 50);

	//Animation delay setter
	//Args
	//Uint32 animationDelay - animation delay (in ms)
	void setAnimationDelay(Uint32 animationDelay);

	//Number of frames setter
	//Args:
	//Uint32 numOfFrames - number of animation frames
	void setNumOfFrames(Uint32 numOfFrames);

	//(I) Rendering method
	//Args:
	//int x - X screen coordinate
	//int y - Y screen coordinate
	//SDL_Rect* clip - clipping rectangle
	//double a - rotation angle (0-359)
	//SDL_Point* c - rotation center
	//SDL_RendererFlip f - SDL renderer flip flag
	virtual void render(int x, int y, SDL_Rect* clip = NULL, double a = 0, SDL_Point* c = NULL, SDL_RendererFlip f = SDL_FLIP_NONE);

	//Destructor
	virtual ~Sprite();

private:
	
	//Animation frame clipping rectangle
	SDL_Rect mAnimationFrame;

	//Current frame counter
	Uint32 miCurrentFrame;

	//Animation timer
	Uint32 miAnimationTimer;

	//Animation delay
	Uint32 miAnimationDelay;

	//Number of animation frames
	Uint32 miNumOfFrames;
		
};

#endif
