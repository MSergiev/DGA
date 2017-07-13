/*
 * Dice.h
 *
 *  Created on: Jul 9, 2017
 *      Author: Puzz
 */

#ifndef DICE_H
#define DICE_H
#include <ctime>
#include "Sprite.h"
#include "Texture.h"
#include "Shared.h"
#include <vector>
#include <cstdlib>
using std::rand;
using std::srand;
using std::time;
//Dice constants
int DICE_WIDTH = 200;
int DICE_HEIGHT = 200;

SDL_Rect Sides[6][6];
std::vector<SDL_Rect> sides;
SDL_Texture * DiceTexture = NULL;
class Dice {
public:
	Dice();
	virtual ~Dice();
	void free();
	void cropAllDiceSides();
	void setAllSides();
	int roll();
	void Event();
	void init();
};

#endif /* DICE_H */
