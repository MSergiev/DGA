#include "Sprite.h"

Sprite::Sprite(SDL_Rect frameSize, Uint32 numOfFrames, Uint32 animationDelay){
	//Initialize data
	setNumOfFrames(numOfFrames);
	setAnimationDelay(animationDelay);
	miAnimationTimer = SDL_GetTicks();
	miCurrentFrame = 0;

	//Initialize animation frame
	mAnimationFrame = frameSize;
	miInitX = frameSize.x;
	miInitY = frameSize.y;
}

void Sprite::setAnimationDelay(Uint32 animationDelay){
	this->miAnimationDelay = animationDelay;
}

void Sprite::setNumOfFrames(Uint32 numOfFrames){
	this->miNumOfFrames = numOfFrames;
}

void Sprite::setAnimationFrame(SDL_Rect animationFrame){
	this->mAnimationFrame.x = animationFrame.x;
	this->mAnimationFrame.y = animationFrame.y;
	this->mAnimationFrame.w = animationFrame.w;
	this->mAnimationFrame.h = animationFrame.h;
	this->miInitX = animationFrame.x;
	this->miInitY = animationFrame.y;
}

void Sprite::render(int x, int y, double s, SDL_Rect* clip, double a, SDL_Point* c, SDL_RendererFlip f){
	//If enough time has passed
	if(SDL_GetTicks()-miAnimationTimer > miAnimationDelay){
		//If we are not on the last frame
		if(miCurrentFrame < miNumOfFrames-1){
			//If spritesheet row end has not been reached
			if(mAnimationFrame.x+mAnimationFrame.w < getWidth()){
				//Go to next frame
				mAnimationFrame.x+=mAnimationFrame.w;
			//If spritesheet row end has been reached
			} else {
				//Go to next row of frames
				mAnimationFrame.x = 0;
				mAnimationFrame.y+=mAnimationFrame.h;
			}
			//Increment current frame counter
			miCurrentFrame++;
		//If we are on the last frame
		} else {
			//Go back to the first frame
			mAnimationFrame.x = miInitX;
			mAnimationFrame.y = miInitY;
			//Reset current frame counter
			miCurrentFrame = 0;
		}
		//Restart animation timer
		miAnimationTimer = SDL_GetTicks();
	}

	//Render part of sprite
	if(clip!=NULL){
		SDL_Rect clipped;
		clipped.x = mAnimationFrame.x+clip->x;
		clipped.y = mAnimationFrame.y+clip->y;
		clipped.w = mAnimationFrame.x+clip->w;
		clipped.h = mAnimationFrame.y+clip->h;
		Texture::render(x,y,s,&clipped,a,c,f);	
	}
	else 
	//Render sprite	
		Texture::render(x,y,s,&mAnimationFrame,a,c,f);

}

Sprite::~Sprite(){
}

