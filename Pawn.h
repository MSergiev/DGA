/*
 * Pawn.h
 *
 *  Created on: 10.07.2017 ã.
 *      Author: IVY
 */

#ifndef PAWN_H_
#define PAWN_H_

#define SPRITE_SIZE 65
#define ANIMATION_DELAY 25
#define NUM_OF_FRAMES 20

///Include sprite class
#include "Sprite.h"
#include "Shared.h"

#include <iostream>
using std::endl;
using std::cout;
using std::cerr;
using std::string;

#include <vector>
using std::vector;

class Pawn
{
private:
	int m_iXPosition, m_iYPosition;
	//Flag if pawn is on the final field
	//Scale factor
	double m_dScale;
	//Pawn final square position
	//int m_iFinished;
	//Pawn is idle flag
	// the flag used to say if the pawn walks or sits
	bool m_bIdle;
	// relative to start position
	int m_iPosition;
	// pawn color
	Colors m_eColor;
	
	///Sprite object pointer
	Sprite mPlayerSprite;

	// method that set the right picture of the pawn
	void setAnimationFrame();

public:
	Pawn(Colors c);
	virtual ~Pawn();

	///Rendering method
	///Args:
	///int x - X screen coordinate
	///int y - Y screen coordinate
	void render(int x, int y);

	/// setters & getters
	int getIXPosition() const;
	void setIXPosition(int iXPosition);

	int getIYPosition() const;
	void setIYPosition(int iYPosition);

	int getIPosition() const;
	void setIPosition(int iPosition);
	
	double getDScale() const;
	void setDScale(double dScale);
	
	//int getIFinished() const;
	//void setIFinished(int iFinished);

	bool getBIdle() const;
	void setBIdle(bool bIdle);
	
	Colors getEColor() const;
	void setEColor(Colors eColor);
};

#endif /* PAWN_H_ */
