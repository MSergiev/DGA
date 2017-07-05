#include "Player.h"

Player::Player() {
	//Initialize data
	miAnimationTimer = SDL_GetTicks();
	miCurrentFrame = 0;

	//Initialize animation frame
	mAnimationFrame.x = 0;
	mAnimationFrame.y = 0;
	mAnimationFrame.w = SPRITE_SIZE;
	mAnimationFrame.h = SPRITE_SIZE;
}

void Player::setRenderer(SDL_Renderer * renderer){
	//Load spritesheet texture
	if(renderer!=NULL){
		mSprite.setRenderer(renderer);
		mSprite.load("./GFX/bomb.png");
	}
}

void Player::render(int x, int y){
	//If enough time has passed
	if(SDL_GetTicks()-miAnimationTimer > ANIMATION_DELAY){
		//If we are not on the last frame
		if(miCurrentFrame < NUM_OF_FRAMES-1){
			//If spritesheet row end has not been reached
			if(mAnimationFrame.x+SPRITE_SIZE < mSprite.getWidth()){
				//Go to next frame
				mAnimationFrame.x+=SPRITE_SIZE;
			//If spritesheet row end has been reached
			} else {
				//Go to next row of frames
				mAnimationFrame.x = 0;
				mAnimationFrame.y+=SPRITE_SIZE;
			}
			//Increment current frame counter
			miCurrentFrame++;
		//If we are on the last frame
		} else {
			//Go back to the first frame
			mAnimationFrame.x = 0;
			mAnimationFrame.y = 0;
			//Reset current frame counter
			miCurrentFrame = 0;
		}
		//Restart animation timer
		miAnimationTimer = SDL_GetTicks();
	}

	//Render sprite
	mSprite.render(x, y, &mAnimationFrame);
}

void Player::free(){
	//Free resources
	mSprite.free();
	mSprite = NULL;
}

Player::~Player(){}
