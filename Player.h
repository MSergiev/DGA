//Player class

#ifndef PLAYER_H
#define PLAYER_H

#include "Pawn.h"

class Player{
private:

	// private members
	// TO DO: delete everything with positions
	Colors m_EColor;
	int m_iSteps;
	int m_iTaken;
	int m_iHadTaken;
	int m_iActivePawns;
	int m_iDiceRoll;

	// private method
	void SetPawnsVector();

public:
	//Constructor
	Player(Colors color);

	// methods
	void Print();
	void Render(vector<pair<int, int> > pos);
	vector<int> GetPositions();
	void SetRenderer(SDL_Renderer* renderer);

	// setters and getters
	int getIHadTaken() const;
	void setIHadTaken(int iHadTaken);

	int getIPlayerPosition() const;
	void setIPlayerPosition(int iPlayerPosition);

	int getISteps() const;
	void setISteps(int iSteps);

	int getITaken() const;
	void setITaken(int iTaken);

	int getIActivePawns() const;
	void setIActivePawns(int iActivePawns);

	int getIDiceRoll() const;
	void setIDiceRoll(int iDiceRoll);

	Colors getEColor() const;
	void setEColor(Colors eColor);

	//Destructor
	~Player();
	
	//Vector of player pawn pointers
	vector< Pawn* > m_vPawns;
};

#endif
