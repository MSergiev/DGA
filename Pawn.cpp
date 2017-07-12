/*
 * Pawn.cpp
 *
 *  Created on: 10.07.2017 ã.
 *      Author: IVY
 */

#include "Pawn.h"

Pawn::Pawn()
		: m_uiPosition(), m_strColor()
{
	//Initialize frame dimensions
	SDL_Rect frame = { 0, 0, SPRITE_SIZE, SPRITE_SIZE };
	//Create sprite object
	mPlayerSprite = new Sprite(frame, NUM_OF_FRAMES, ANIMATION_DELAY);

}

Pawn::~Pawn()
{
	//Release resources
	mPlayerSprite->free();
	delete mPlayerSprite;
}

void Pawn::render()
{
	//Render sprite
	mPlayerSprite->render(m_uiPosition, 0);
}

void Pawn::setRenderer(SDL_Renderer* renderer)
{
	mPlayerSprite->setRenderer(renderer);
	mPlayerSprite->load("./GFX/bomb.png");
}
