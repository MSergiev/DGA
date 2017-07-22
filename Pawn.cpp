/*
 * Pawn.cpp
 *
 *  Created on: 10.07.2017 ã.
 *      Author: IVY
 */

#include "Pawn.h"

Pawn::Pawn(Colors c)
{
	// make a SDL_Rect to set the dimensions of the pawn
	SDL_Rect rect = { 0, 0, SPRITE_SIZE, SPRITE_SIZE };
	// init the constructor of the sprite
	mPlayerSprite = new Sprite(rect, PAWN_FRAMES, 20);
	// set the right color
	setEColor(c);
	// set the position in the base
	setIPosition(-1);
	// load the image of the pawn
	mPlayerSprite->load(PAWN_PATH);
}

// methods
void Pawn::render(int x, int y)
{
	//Render sprite
	mPlayerSprite->render(x, y);
}

// destructor
Pawn::~Pawn()
{
	//Release resources
	mPlayerSprite->free();
}

// setters & getters

int Pawn::getIPosition() const
{
	return m_iPosition;
}

Colors Pawn::getEColor() const
{
	return m_eColor;
}

void Pawn::setEColor(Colors eColor)
{
	//Initialize frame dimensions
	SDL_Rect frame = { 0, (eColor - 1) * SPRITE_SIZE * 6, SPRITE_SIZE,
			SPRITE_SIZE };
	// set it in the animation frame
	mPlayerSprite->setAnimationFrame(frame);
	// change the color
	m_eColor = eColor;
}

void Pawn::setIPosition(int iPosition)
{
	m_iPosition = iPosition;
}
