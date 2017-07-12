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
#include <cstdlib>
using std::rand;
using std::srand;
using std::clock;

class Dice {
public:
	Dice();
	virtual ~Dice();
	int roll();
	void Event();
	void init();
};

#endif /* DICE_H */
