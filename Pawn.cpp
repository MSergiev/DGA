/*
 * Pawn.cpp
 *
 *  Created on: 10.07.2017 ?.
 *      Author: IVY
 */

#include "Pawn.h"

Pawn::Pawn(Colors c)
		:mPlayerSprite(SDL_Rect {0,0,SPRITE_SIZE, SPRITE_SIZE}, PAWN_FRAMES, 20)
{
	setEColor(c);
	setIXPosition(-1);
	setIYPosition(-1);
	setBFinished(0);
	mPlayerSprite.load(PAWN_PATH);
}

// methods
void Pawn::render(int x, int y)
{
	//Render sprite
	mPlayerSprite.render(x, y);
}

// destructor
Pawn::~Pawn()
{
	//Release resources
	//delete mPlayerSprite;
}

// setters & getters

int Pawn::getIXPosition() const
{
	return m_iXPosition;
}

int Pawn::getIYPosition() const
{
	return m_iYPosition;
}

bool Pawn::getBFinished() const
{
	return m_bFinished;
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
	mPlayerSprite.setAnimationFrame(frame);
	//mPlayerSprite = new Sprite(frame, NUM_OF_FRAMES, ANIMATION_DELAY);
	m_eColor = eColor;
}

void Pawn::setIXPosition(int iXPosition)
{
	m_iXPosition = iXPosition;
}
void Pawn::setIYPosition(int iYPosition)
{
	m_iYPosition = iYPosition;
}
void Pawn::setBFinished(bool bFinished)
{
	m_bFinished = bFinished;
}
