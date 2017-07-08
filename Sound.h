/*
 * SoundEffects.h
 *
 *  Created on: Jul 6, 2017
 *      Author: Puzz
 */

#ifndef SOUNDEFFECTS_H_
#define SOUNDEFFECTS_H_
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
using std::cerr;
using std::endl;
enum SEFFECTS {bruh,camera,censor,ding,drumroll,fatality,finishhim,
flashback,fuck,fuckedup,fucku,gotcha,headshot,helpme,here,hitmarker,
idgaf,inception,jeff,mario,more,punch,s21,scratch,smokeweed,sparta,
sudden,suprise,whoosh};
class SoundEffects {
public:
	SoundEffects();
	static bool load();
	static void pause();
	static bool playing();
	static void free();
	static Mix_Chunk* Seffects[29];
	static void play(SEFFECTS sound);
	virtual ~SoundEffects();
private:
	//static Mix_Chunk* Seffects[29];
};

#endif /* SOUNDEFFECTS_H_ */
