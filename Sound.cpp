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
	Seffects[0] = Mix_LoadWAV("./SFX/accend.wav");
	Seffects[1] = Mix_LoadWAV("./SFX/accend2.wav");
	Seffects[2] = Mix_LoadWAV("./SFX/boink.wav");
	Seffects[3] = Mix_LoadWAV("./SFX/boink2.wav");
	Seffects[4] = Mix_LoadWAV("./SFX/camera.wav");
	Seffects[5] = Mix_LoadWAV("./SFX/censor.wav");
	Seffects[6] = Mix_LoadWAV("./SFX/click.wav");
	Seffects[7] = Mix_LoadWAV("./SFX/DiceRoll.wav");
	Seffects[8] = Mix_LoadWAV("./SFX/ding.wav");
	Seffects[9] = Mix_LoadWAV("./SFX/drumroll.wav");
	Seffects[10] = Mix_LoadWAV("./SFX/explosion.wav");
	Seffects[11] = Mix_LoadWAV("./SFX/fuseBomb.wav");
	Seffects[12] = Mix_LoadWAV("./SFX/jump.wav");
	Seffects[13] = Mix_LoadWAV("./SFX/pop.wav");
	Seffects[14] = Mix_LoadWAV("./SFX/SciFi.wav");
	Seffects[15] = Mix_LoadWAV("./SFX/punch.wav");
	Seffects[16] = Mix_LoadWAV("./SFX/scratch.wav");
	Seffects[17] = Mix_LoadWAV("./SFX/taken.wav");
	Seffects[18] = Mix_LoadWAV("./SFX/typing.wav");
	Seffects[19] = Mix_LoadWAV("./SFX/whisle.wav");
	Seffects[20] = Mix_LoadWAV("./SFX/whisleSlide.wav");
	Seffects[21] = Mix_LoadWAV("./SFX/whislewind.wav");
	Seffects[22] = Mix_LoadWAV("./SFX/whoosh.wav");
	Seffects[23] = Mix_LoadWAV("./SFX/orchHit.wav");

	//gives error if  the the sounds effects are NOT loaded correctly.
	for(int i = 0; i < SFX_NUM; ++i){
		if(Seffects[i]==NULL){
			cerr << "Seffects error: " << Mix_GetError() << endl;
			success = false;
		}
	}

	mus[0] = Mix_LoadMUS("./BGM/menuS.mp3");
	mus[1] = Mix_LoadMUS("./BGM/ambient.wav");
	mus[2] = Mix_LoadMUS("./BGM/electric.wav");
	mus[3] = Mix_LoadMUS("./BGM/rock.wav");
	
	//gives error if  the the music is NOT loaded correctly.
	for(int i = 0; i < BGM_NUM; ++i){
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
	for (int i = 0; i < SFX_NUM; i++) {
		Mix_FreeChunk(Seffects[i]);
		Seffects[i] = NULL;
	}
	// frees/clear's the  used memory that the music used
	for (int i = 0; i < BGM_NUM; i++) {
		Mix_FreeMusic(mus[i]);
		mus[i] = NULL;
	}
}
// Mothod that plays  the sound effects
void Sound::play(SEFFECTS sound)
{
	if(!mute){
		switch(sound){
			case accend:
				Mix_PlayChannel(-1, Seffects[0], 0);
				break;
			case accend2:
					Mix_PlayChannel(-1, Seffects[1], 0);
				break;
			case boink:
				Mix_PlayChannel(-1, Seffects[2], 0);
				break;
			case boink2:
				Mix_PlayChannel(-1, Seffects[3], 0);
				break;
			case camera:
				Mix_PlayChannel(-1, Seffects[4], 0);
					break;
			case censor:
				Mix_PlayChannel(-1, Seffects[5], 0);
				break;
			case click:
				Mix_PlayChannel(-1, Seffects[6], 0);
				break;
			case DiceRoll:
				Mix_PlayChannel(-1, Seffects[7], 0);
				break;
			case ding:
				Mix_PlayChannel(-1, Seffects[8], 0);
				break;
			case drumroll:
				Mix_PlayChannel(-1, Seffects[9], 0);
				break;
			case explosion:
				Mix_PlayChannel(-1, Seffects[10], 0);
				break;
			case fuseBomb:
				Mix_PlayChannel(-1, Seffects[11], 0);
				break;
			case jump:
				Mix_PlayChannel(-1, Seffects[12], 0);
				break;
			case pop:
				Mix_PlayChannel(-1, Seffects[13], 0);
				break;
			case punch:
				Mix_PlayChannel(-1, Seffects[14], 0);
					break;
			case SciFi:
				Mix_PlayChannel(-1, Seffects[15], 0);
				break;
			case scratch:
				Mix_PlayChannel(-1, Seffects[16], 0);
				break;
			case taken:
				Mix_PlayChannel(-1, Seffects[17], 0);
				break;
			case typing:
				Mix_PlayChannel(-1, Seffects[18], 0);
				break;
			case whisle:
				Mix_PlayChannel(-1, Seffects[19], 0);
				break;
			case whisleSlide:
				Mix_PlayChannel(-1, Seffects[20], 0);
					break;
			case whislewind:
				Mix_PlayChannel(-1, Seffects[21], 0);
				break;
			case whoosh:
				Mix_PlayChannel(-1, Seffects[22], 0);
				break;
			case orchHit:
				Mix_PlayChannel(-1, Seffects[23], 0);
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
		Mix_VolumeMusic(64);
		switch(music){
			case menuS:
				Mix_PlayMusic(mus[0], -1);
				break;
			case ambient:
				Mix_PlayMusic(mus[1], -1);
				break;
			case electric:
				Mix_PlayMusic(mus[2], -1);
				break;
			case rock:
				Mix_PlayMusic(mus[3], -1);
				break;
		}
		}
	}
}
// empty destructor
Sound::~Sound() {
}

