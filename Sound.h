/*
 * Sound.h
 *
 *  Created on: Jul 6, 2017
 *      Author: Puzz
 */

#ifndef SOUND_H_
#define SOUND_H_
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
using std::cerr;
using std::endl;
//  sorted sound effects
enum SEFFECTS {accend,accend2,boink,boink2,camera,censor,click,DiceRoll
,ding,drumroll,explosion,fuseBomb,jump,pop,SciFi,punch,scratch,taken,
typing,whisle,whisleSlide,whislewind,whoosh
};
//  sorted music  effects
enum MUSIC{menuS};

class Sound {
public:
	// flag to mute sound
	static bool mute;
	
	Sound();
	static bool load();
	static void pause();
	static bool playing();
	static void free();
	static void play(SEFFECTS sound);
	static void music(MUSIC music);
	virtual ~Sound();
private:
	// static massives/arrays that can be accessed by static methods.
	static Mix_Chunk* Seffects[23];
	static Mix_Music* mus[1];
};

#endif /* SOUND_H_ */
