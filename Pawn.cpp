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
	setIPosition(0);
	setIXPosition(-1);
	setIYPosition(-1);
	setDScale(1);
	setBIdle(1);
	mPlayerSprite.load(PAWN_PATH);
}

// methods
void Pawn::render(int x, int y)
{
	//Render sprite
	mPlayerSprite.render(x, y, m_dScale);
}

// destructor
Pawn::~Pawn()
{
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

int Pawn::getIPosition() const
{
	return m_iPosition;
}

bool Pawn::getBIdle() const
{
	return m_bIdle;
}

double Pawn::getDScale() const
{
	return m_dScale;
}

Colors Pawn::getEColor() const
{
	return m_eColor;
}

void Pawn::setAnimationFrame()
{
	//Initialize frame dimensions
	SDL_Rect frame = { 0, (m_eColor-1)*SPRITE_SIZE*6+m_bIdle*3*SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE };
	//Set sprite animation frame
	mPlayerSprite.setAnimationFrame(frame);
}

void Pawn::setEColor(Colors eColor)
{
	m_eColor = eColor;
	setAnimationFrame();
}

void Pawn::setIXPosition(int iXPosition)
{
	m_iXPosition = iXPosition;
}
void Pawn::setIYPosition(int iYPosition)
{
	m_iYPosition = iYPosition;
}
void Pawn::setIPosition(int iPosition)
{
	m_iPosition = iPosition;
}
void Pawn::setDScale(double dScale)
{
	m_dScale = dScale;
}
void Pawn::setBIdle(bool bIdle)
{
	m_bIdle = bIdle;
	setAnimationFrame();
}
