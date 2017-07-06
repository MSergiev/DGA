#include "Player.h"

Player::Player() {
	//Initialize frame dimensions
	SDL_Rect frame = {0, 0, SPRITE_SIZE, SPRITE_SIZE};
	//Create sprite object
	mPlayerSprite = new Sprite(frame, NUM_OF_FRAMES, ANIMATION_DELAY);
}

void Player::render(int x, int y){
	//Render sprite
	mPlayerSprite->render(x, y);
}

void Player::setRenderer(SDL_Renderer* renderer){
	mPlayerSprite->setRenderer(renderer);
	mPlayerSprite->load("./GFX/bomb.png");	
}

Player::~Player(){
	//Release resources
	mPlayerSprite->free();
	delete mPlayerSprite;
}
