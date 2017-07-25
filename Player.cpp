#include "Player.h"

Player::Player(Colors color)
		: m_iSteps(), m_iTaken(), m_iLost()
{
	// set the active pawns to zero
	setIActivePawns(0);
	// put the dice with correct default value
	setIDiceRoll(1);
	// at the begging of the game no one is finished
	setIFinishPosition(0);
	// it set the color of the pawns and the player
	setEColor(color);
	// sets the pawns vector with empty values
	SetPawnsVector();
}

Player::~Player()
{
	for (unsigned int i = 0; i < m_vPawns.size(); i++)
	{
		// delete all the pawns in the vector
		// the vector is made with dynamically allocated memory
		delete m_vPawns[i];
		m_vPawns[i] = NULL;
	}
}

template<typename Key, typename Value>
bool Player::isKeyInMap(map<Key, Value> &theMap, const Key &key)
{
	return theMap.find(key) != theMap.end();
}

void Player::Render(vector<pair<int, int> > pos)
{
	// the actual render method -
	// pass the data of the positions of every pawn
	// pos[i].first - x on the board
	// pos[i].second - y on the board

	if (pos.size() == 0)
	{
		cerr << "The vector of the pawns is empty." << endl;
	}

	//Map object: coordinate pair -> vector of pawns with these coordinates
	map<pair<int, int>, vector<Pawn*> > mapToCount;
	//Map iterator
	map<pair<int, int>, vector<Pawn*> >::iterator it;

	//Traverse position vector
	for (unsigned int i = 0; i < pos.size(); i++)
	{
		//Create key pair
		pair<int, int> key = {pos[i].first, pos[i].second};
		//Push pawn in map vector
		mapToCount[key].push_back(m_vPawns[i]);
	}
	
	//Traverse map
	for (it = mapToCount.begin(); it!=mapToCount.end(); ++it)
	{
		//Traverse map vector
		for(unsigned i = 0; i < it->second.size(); i++)
		{
			//Scale factor
			float scale = (1/(float)it->second.size());
			//Set pawn scale
			it->second[i]->setDScale(scale);
			//Render pawn
			it->second[i]->render(it->first.first+i*SPRITE_SIZE*scale,
							it->first.second-15+i*SPRITE_SIZE*scale);
		}
	}
}

void Player::Print()
{
	cout << "Color: " << getEColor() << endl << "Steps: "
			<< getISteps() << endl << "Taken: " << getITaken() << endl
			<< "Lost: " << getILost() << endl << "Active: "
			<< getIActivePawns() << endl << "Roll: " << getIDiceRoll()
			<< endl << "Pawn positions:" << endl;

	// for every pawn
	for (unsigned i = 0; i < m_vPawns.size(); i++)
	{
		// print in the console the position
		cout << "(" << m_vPawns[i]->getIXPosition() << ", "
				<< m_vPawns[i]->getIYPosition() << ") ";
	}
	cout << endl;
}

// setters and getters
int Player::getILost() const
{
	return m_iLost;
}

void Player::setILost(int iLost)
{
	m_iLost = iLost;
}

int Player::getISteps() const
{
	return m_iSteps;
}

void Player::setISteps(int iSteps)
{
	m_iSteps = iSteps;
}

int Player::getITaken() const
{
	return m_iTaken;
}

void Player::setITaken(int iTaken)
{
	m_iTaken = iTaken;
}

int Player::getIActivePawns() const
{
	return m_iActivePawns;
}

void Player::setIActivePawns(int iActivePawns)
{
	m_iActivePawns = iActivePawns;
}

int Player::getIDiceRoll() const
{
	return m_iDiceRoll;
}

void Player::setIDiceRoll(int iDiceRoll)
{
	if (iDiceRoll >= 1 && iDiceRoll <= 6)
		m_iDiceRoll = iDiceRoll;
}

Colors Player::getEColor() const
{
	return m_EColor;
}

int Player::getIFinishPosition() const
{
	return m_iFinishPosition;
}

void Player::setIFinishPosition(int iFinishPosition)
{
	m_iFinishPosition = iFinishPosition;
}

void Player::setEColor(Colors eColor)
{
	// set the color of the player
	m_EColor = eColor;

	// for each pawn
	for (unsigned i = 0; i < m_vPawns.size(); i++)
	{
		// pass the color
		m_vPawns[i]->setEColor(m_EColor);
	}

}

void Player::SetPawnsVector()
{
	for (unsigned int i = 0; i < PAWNS; i++)
	{
		//make a dynamic allocated pawn
		Pawn* pawn = new Pawn(m_EColor);

		// give it to the vector
		m_vPawns.push_back(pawn);

		// set position into base
		m_vPawns.back()->setIXPosition(
				BASE_SQUARES[m_EColor - 1][i].first);
		m_vPawns.back()->setIYPosition(
				BASE_SQUARES[m_EColor - 1][i].second);
	}
}
