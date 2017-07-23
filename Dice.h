/*
 * Dice.h
 *
 *  Created on: Jul 9, 2017
 *      Author: Puzz
 */

#ifndef DICE_H
#define DICE_H

#include <ctime>
#include "Texture.h"
#include "Shared.h"
#include <vector>
#include <cstdlib>
using std::rand;
using std::srand;
using std::time;

///Dice constants
#define DICE_WIDTH  148
#define DICE_HEIGHT  148

class Dice {
public:
	Dice();
	virtual ~Dice();
	void render();
	void setPosition(int x, int y);
	void setDiceResult(int DiceResult);
	int roll();
	bool Event(SDL_Event& e);
	void init();
private:
	int posX, posY;
	int DiceResult;
	Texture  DiceTexture;
};

#endif /* DICE_H */
