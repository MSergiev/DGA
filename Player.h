//Player class

#ifndef PLAYER_H
#define PLAYER_H

#include "Pawn.h"

class Player{
private:
	// private vector member
	vector< Pawn* > m_vPawns;

	// private members
	// TO DO: delete everything with positions
	Colors m_EColor;
	int m_iSteps;
	int m_iTaken;
	int m_iHadTaken;

	// private method
	void SetPawnsVector();

public:
	//Constructor
	Player(Colors color);

	// methods
	void Print();
	void Render(int x, int y);
	vector<int> GetPositions();
	void SetRenderer(SDL_Renderer* renderer);

	void movePawn(unsigned int numberOfPawn, int x, int y);

	// setters and getters
	int getIHadTaken() const;
	void setIHadTaken(int iHadTaken);

	int getIPlayerPosition() const;
	void setIPlayerPosition(int iPlayerPosition);

	int getISteps() const;
	void setISteps(int iSteps);

	int getITaken() const;
	void setITaken(int iTaken);

	Colors getEColor() const;
	void setEColor(Colors eColor);

	const vector<Pawn*>& getVPawns() const;


	//Destructor
	~Player();
};

#endif
