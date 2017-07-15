/*
 * Pawn.cpp
 *
 *  Created on: 10.07.2017 ã.
 *      Author: IVY
 */

#include "Pawn.h"

Pawn::Pawn()
		: m_eColor()
{
	setUiPosition(0);
}

// methods
void Pawn::render(int x, int y)
{
	//Render sprite
	mPlayerSprite->render(x, y);
}

void Pawn::setRenderer(SDL_Renderer* renderer)
{
	mPlayerSprite->setRenderer(renderer);
	mPlayerSprite->load(PAWN_PATH);
}


// destructor
Pawn::~Pawn()
{
	//Release resources
	delete mPlayerSprite;
}

// setters & getters

unsigned int Pawn::getUiPosition() const
{
	return m_uiPosition;
}

Colors Pawn::getEColor() const
{
	return m_eColor;
}


void Pawn::setEColor(Colors eColor)
{
	//Initialize frame dimensions
	SDL_Rect frame = { 0, (eColor-1)*SPRITE_SIZE*6, SPRITE_SIZE, SPRITE_SIZE };
	//Create sprite object
	mPlayerSprite = new Sprite(frame, NUM_OF_FRAMES, ANIMATION_DELAY);
	m_eColor = eColor;
}

void Pawn::setUiPosition(unsigned int uiPosition)
{
	m_uiPosition = uiPosition;
}
