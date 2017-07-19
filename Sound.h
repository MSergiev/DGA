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
enum SEFFECTS {bruh,camera,censor,ding,drumroll,fatality,finishhim,
flashback,fuck,fuckedup,fucku,gotcha,headshot,helpme,here,hitmarker,
idgaf,inception,jeff,mario,more,punch,s21,scratch,smokeweed,sparta,
sudden,suprise,whoosh};
//  sorted music  effects
enum MUSIC{rock,electric,ambient};

class Sound {
public:
	Sound();
	static bool load();
	static void pause();
	static bool playing();
	static void free();
	static void play(SEFFECTS sound);
	static void music(MUSIC music);
	virtual ~Sound();
private:
	// static massives   that allows us to use them in diffrend classes
	static Mix_Chunk* Seffects[29];
	static Mix_Music* mus[3];
};

#endif /* SOUND_H_ */
