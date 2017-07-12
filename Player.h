//Player class

#ifndef PLAYER_H
#define PLAYER_H

#include "Pawn.h"

class Player{
public:
	//Constructor
	Player();

	void print();

	void render();

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
	vector< Pawn* > m_vPawns;

	int m_iPlayerPosition;
	string m_strColor;
	int m_iSteps;
	int m_iTaken;
	int m_iHadTaken;
};

#endif
