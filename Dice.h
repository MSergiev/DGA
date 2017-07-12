/*
 * Dice.h
 *
 *  Created on: Jul 9, 2017
 *      Author: Puzz
 */

#ifndef SRC_DICE_H_
#define SRC_DICE_H_
#include <iostream>
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <cstdlib>
using namespace std;

class Dice {
public:
	Dice();
	virtual ~Dice();
	bool init();
	bool loadMedia();
	void close();
private:
	static void roll();
	static void Event();

};

#endif /* SRC_DICE_H_ */
