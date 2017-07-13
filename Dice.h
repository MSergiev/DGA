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
using std::time;

class Dice {
public:
	Dice();
	virtual ~Dice();
	//SDL_Renderer* renderer - renderer to draw the board with
		void setRenderer(SDL_Renderer* renderer);
		//Rendering method
		void render();
		//Resource releasing method
	void free();
	int roll();
	void Event();
	void init();
};

#endif /* DICE_H */
