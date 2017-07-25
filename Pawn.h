/*
 * Pawn.h
 *
 *  Created on: 10.07.2017 �.
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
	//Pawn is on final square flag
	bool m_bFinished;
	//Pawn is idle flag
	bool m_bIdle;
	Colors m_eColor;
	
	///Sprite object pointer
	Sprite mPlayerSprite;

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

	double getDScale() const;
	void setDScale(double dScale);
	
	bool getBFinished() const;
	void setBFinished(bool bFinished);

	bool getBIdle() const;
	void setBIdle(bool bIdle);
	
	Colors getEColor() const;
	void setEColor(Colors eColor);
};

#endif /* PAWN_H_ */
