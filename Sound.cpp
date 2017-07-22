/*
 * Sound.cpp
 *
 *  Created on: Jul 6, 2017
 *      Author: Puzz
 */

#include "Sound.h"
// massives/arrays that keep the soundeffects and  music
Mix_Chunk* Sound::Seffects[];
Mix_Music* Sound::mus[];
bool Sound::mute = 0;

//empty constructor
Sound::Sound()
{
}
// load's the sound effects
bool Sound::load(){
	bool success = true;
	if(SDL_Init(SDL_INIT_AUDIO)<0){
		cerr << "SDL Audio error: " << SDL_GetError() << endl;
		success = false;
	}
	if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048)<0){
		cerr << "Audio error: " << Mix_GetError() << endl;
		success = false;
	}
	Seffects[0] = Mix_LoadWAV("SFX/bruh.wav");
	Seffects[1] = Mix_LoadWAV("SFX/camera.wav");
	Seffects[2] = Mix_LoadWAV("SFX/censor.wav");
	Seffects[3] = Mix_LoadWAV("SFX/ding.wav");
	Seffects[4] = Mix_LoadWAV("SFX/drumroll.wav");
	Seffects[5] = Mix_LoadWAV("SFX/fatality.wav");
	Seffects[6] = Mix_LoadWAV("SFX/finishhim.wav");
	Seffects[7] = Mix_LoadWAV("SFX/flashback.wav");
	Seffects[8] = Mix_LoadWAV("SFX/fuck.wav");
	Seffects[9] = Mix_LoadWAV("SFX/fuckedup.wav");
	Seffects[10] = Mix_LoadWAV("SFX/fucku.wav");
	Seffects[11] = Mix_LoadWAV("SFX/gotcha.wav");
	Seffects[12] = Mix_LoadWAV("SFX/whoosh.wav");
	Seffects[13] = Mix_LoadWAV("SFX/headshot.wav");
	Seffects[14] = Mix_LoadWAV("SFX/helpme.wav");
	Seffects[15] = Mix_LoadWAV("SFX/here.wav");
	Seffects[16] = Mix_LoadWAV("SFX/hitmarker.wav");
	Seffects[17] = Mix_LoadWAV("SFX/idgaf.wav");
	Seffects[18] = Mix_LoadWAV("SFX/inception.wav");
	Seffects[19] = Mix_LoadWAV("SFX/jeff.wav");
	Seffects[20] = Mix_LoadWAV("SFX/mario.wav");
	Seffects[21] = Mix_LoadWAV("SFX/more.wav");
	Seffects[22] = Mix_LoadWAV("SFX/punch.wav");
	Seffects[23] = Mix_LoadWAV("SFX/s21.wav");
	Seffects[24] = Mix_LoadWAV("SFX/scratch.wav");
	Seffects[25] = Mix_LoadWAV("SFX/smokeweed.wav");
	Seffects[26] = Mix_LoadWAV("SFX/sparta.wav");
	Seffects[27] = Mix_LoadWAV("SFX/sudden.wav");
	Seffects[28] = Mix_LoadWAV("SFX/suprise.wav");
	//gives error if  the the sounds effects are NOT loaded correctly.
	for(int i = 0; i < 28; ++i){
		if(Seffects[i]==NULL){
			cerr << "Seffects error: " << Mix_GetError() << endl;
			success = false;
		}
	}
	mus[0] = Mix_LoadMUS("BGM/rock.wav");
	mus[1] = Mix_LoadMUS("BGM/ambient.wav");
	mus[2] = Mix_LoadMUS("BGM/electric.wav");
	//gives error if  the the music is NOT loaded correctly.
	for(int i = 0; i < 3; ++i){
			if(mus[i]==NULL){
				cerr << "music error: " << Mix_GetError() << endl;
				success = false;
			}
		}
	
	return success;
}
//pauses the music
void Sound::pause() {
	Mix_PauseMusic();
}
//checks if the music is playing
bool Sound::playing() {
	return Mix_PlayingMusic();
}
// frees/clear's the  used memory that the sounds used
void Sound::free(){
	for (int i = 0; i < 28; i++) {
		Mix_FreeChunk(Seffects[i]);
		Seffects[i] = NULL;
	}
	// frees/clear's the  used memory that the music used
	for (int i = 0; i < 3; i++) {
		Mix_FreeMusic(mus[i]);
		mus[i] = NULL;
	}
	Mix_Quit();
}
// Mothod that plays  the sound effects
void Sound::play(SEFFECTS sound)
{
	if(!mute){
		switch(sound){
			case bruh:
				Mix_PlayChannel(-1, Seffects[0], 0);
				break;
			case camera:
					Mix_PlayChannel(-1, Seffects[1], 0);
				break;
			case censor:
				Mix_PlayChannel(-1, Seffects[2], 0);
				break;
			case ding:
				Mix_PlayChannel(-1, Seffects[3], 0);
				break;
			case drumroll:
				Mix_PlayChannel(-1, Seffects[4], 0);
					break;
			case fatality:
				Mix_PlayChannel(-1, Seffects[5], 0);
				break;
			case finishhim:
				Mix_PlayChannel(-1, Seffects[6], 0);
				break;
			case flashback:
				Mix_PlayChannel(-1, Seffects[7], 0);
				break;
			case fuck:
				Mix_PlayChannel(-1, Seffects[8], 0);
				break;
			case fuckedup:
				Mix_PlayChannel(-1, Seffects[9], 0);
				break;
			case fucku:
				Mix_PlayChannel(-1, Seffects[10], 0);
				break;
			case gotcha:
				Mix_PlayChannel(-1, Seffects[11], 0);
				break;
			case headshot:
				Mix_PlayChannel(-1, Seffects[12], 0);
				break;
			case helpme:
				Mix_PlayChannel(-1, Seffects[13], 0);
				break;
			case here:
				Mix_PlayChannel(-1, Seffects[14], 0);
					break;
			case hitmarker:
				Mix_PlayChannel(-1, Seffects[15], 0);
				break;
			case idgaf:
				Mix_PlayChannel(-1, Seffects[16], 0);
				break;
			case inception:
				Mix_PlayChannel(-1, Seffects[17], 0);
				break;
			case jeff:
				Mix_PlayChannel(-1, Seffects[18], 0);
				break;
			case mario:
				Mix_PlayChannel(-1, Seffects[19], 0);
				break;
			case more:
				Mix_PlayChannel(-1, Seffects[20], 0);
					break;
			case punch:
				Mix_PlayChannel(-1, Seffects[21], 0);
				break;
			case s21:
				Mix_PlayChannel(-1, Seffects[22], 0);
				break;
			case scratch:
				Mix_PlayChannel(-1, Seffects[23], 0);
				break;
			case smokeweed:
				Mix_PlayChannel(-1, Seffects[24], 0);
				break;
			case sparta:
				Mix_PlayChannel(-1, Seffects[25], 0);
				break;
			case sudden:
				Mix_PlayChannel(-1, Seffects[26], 0);
				break;
			case suprise:
				Mix_PlayChannel(-1, Seffects[27], 0);
					break;
			case whoosh:
				Mix_PlayChannel(-1, Seffects[28], 0);
				break;
			}
		}
	}
// method that plays the music
void Sound::music(MUSIC music){
	if(!mute){
		//resume music if paused
		if(Mix_PlayingMusic()){
			Mix_ResumeMusic();
		}else {
		switch(music){
			case rock:
				Mix_PlayMusic(mus[0], -1);
				break;
			case ambient:
				Mix_PlayMusic(mus[1], -1);
				break;
			case electric:
				Mix_PlayMusic(mus[2], -1);
				break;
	
		}
		}
	}
}
// empty destructor
Sound::~Sound() {
	// TODO Auto-generated destructor stub
}

