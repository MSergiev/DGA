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

//Dice constants
#define DICE_WIDTH  148
#define DICE_HEIGHT  148

class Dice {
public:
	Dice();
	virtual ~Dice();
	void render(Colors c);
	void free();
	void setRenderer(SDL_Renderer* renderer);
	int roll();
	bool Event(SDL_Event& e);
	void init();
private:
	int DiceResult;
	Texture  DiceTexture;
//asd
};

#endif /* DICE_H */
