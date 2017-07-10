//Player class

#ifndef PLAYER_H
#define PLAYER_H

#define SPRITE_SIZE 64
#define ANIMATION_DELAY 25
#define NUM_OF_FRAMES 20

//Include sprite class
#include "Sprite.h"

#include "Pawn.h"

class Player{
public:
	//Constructor
	Player();

	//Rendering method
	//Args:
	//int x - X screen coordinate
	//int y - Y screen coordinate
	void render(int x, int y);

	//Set renderer
	//Args:
	//SDL_Renderer* renderer - renderer to draw the sprites with
	void setRenderer(SDL_Renderer* renderer);

	void print();

	// setters and getters
	int getIHadTaken() const;
	void setIHadTaken(int iHadTaken);

	int getIPlayerPosition() const;
	void setIPlayerPosition(int iPlayerPosition);

	int getISteps() const;
	void setISteps(int iSteps);

	int getITaken() const;
	void setITaken(int iTaken);

	const string& getStrColor() const;
	void setStrColor(const string& strColor);

	//Destructor
	~Player();


private:

	//Sprite object pointer
	//Sprite* mPlayerSprite;

	int m_iPlayerPosition;
	string m_strColor;
	int m_iSteps;
	int m_iTaken;
	int m_iHadTaken;
};

#endif
