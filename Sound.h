<<<<<<< HEAD
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
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
using std::cerr;
using std::endl;
enum SEFFECTS {bruh,camera,censor,ding,drumroll,fatality,finishhim,
flashback,fuck,fuckedup,fucku,gotcha,headshot,helpme,here,hitmarker,
idgaf,inception,jeff,mario,more,punch,s21,scratch,smokeweed,sparta,
sudden,suprise,whoosh};
enum MUSIC{rock,electric,ambient};
class Sound {
public:
	Sound();
	static bool load();
	static void pause();
	static bool playing();
	static void free();
	static Mix_Chunk* Seffects[29];
	static Mix_Music* mus[3];
	static void play(SEFFECTS sound);
	static void music(MUSIC music);
	virtual ~Sound();
private:
	//static Mix_Chunk* Seffects[29];
};

#endif /* SOUND_H_ */
=======
>>>>>>> parent of 1f2efe1... Add files via upload
