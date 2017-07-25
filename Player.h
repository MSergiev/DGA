///Player class

#ifndef PLAYER_H
#define PLAYER_H

#include "Pawn.h"

#include <map>
#include <utility>
using std::map;
using std::pair;

class Player
{
private:
	// private method to help work with map
	template<typename Key, typename Value>
	bool isKeyInMap(map<Key, Value> &theMap, const Key &key);

	/// private members

	/// the color of the player
	Colors m_EColor;

	/// how many steps the player has
	int m_iSteps;

	/// how many enemy paws the player has taken
	int m_iTaken;

	/// how many pawns the player is lost
	int m_iLost;

	/// how many pawns are in the game
	int m_iActivePawns;

	/// what is the last roll of the dice for the player
	int m_iDiceRoll;

	/// at what position the player finished the game
	int m_iFinishPosition;

	/// private method which helps to fill
	/// the vector of the pawns with the necessary info
	void SetPawnsVector();

public:
	///Constructor - wants the color of the player as an argument
	Player(Colors color);

	///Vector of player pawn pointers
	/// its public so it can be used more efficiently and easy
	vector<Pawn*> m_vPawns;

	/// methods
	/// print all the info for the player
	void Print();

	///vector < paint <int,int> > - the x and y:
	/// the positions of all pawns of the player
	void Render(vector<pair<int, int> > pos);

	/// setters and getters
	int getILost() const;
	void setILost(int iLost);

	int getISteps() const;
	void setISteps(int iSteps);

	int getITaken() const;
	void setITaken(int iTaken);

	int getIActivePawns() const;
	void setIActivePawns(int iActivePawns);

	int getIDiceRoll() const;
	void setIDiceRoll(int iDiceRoll);

	int getIFinishPosition() const;
	void setIFinishPosition(int iFinishPosition);

	Colors getEColor() const;
	void setEColor(Colors eColor);

	///Destructor
	~Player();

};

#endif
