/*
 * Pawn.h
 *
 *  Created on: 10.07.2017 ã.
 *      Author: IVY
 */

#ifndef PAWN_H_
#define PAWN_H_

#define SPRITE_SIZE 129
#define ANIMATION_DELAY 25
#define NUM_OF_FRAMES 20

//Include sprite class
#include "Sprite.h"

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
	unsigned int m_uiPosition;
	string m_strColor;

	//Sprite object pointer
	Sprite* mPlayerSprite;
public:
	Pawn();
	virtual ~Pawn();


	//Rendering method
	//Args:
	//int x - X screen coordinate
	//int y - Y screen coordinate
	void render();

	//Set renderer
	//Args:
	//SDL_Renderer* renderer - renderer to draw the sprites with
	void setRenderer(SDL_Renderer* renderer);
	const string& getStrColor() const;

	void setStrColor(const string& strColor);
	unsigned int getUiPosition() const;

	void setUiPosition(unsigned int uiPosition);
	const Sprite*& getPlayerSprite() const;
	void setPlayerSprite(const Sprite*& playerSprite);
};

#endif /* PAWN_H_ */
