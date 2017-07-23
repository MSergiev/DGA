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

void Player::Render(vector<pair<int, int> > pos)
{
	for (unsigned int i = 0; i < pos.size(); i++)
	{
		// the actual render method -
		// pass the data of the positions of every pawn
		// pos[i].first - x on the board
		// pos[i].second - y on the board
		m_vPawns[i]->render(pos[i].first, pos[i].second-15);
	}
}

void Player::Print()
{
	cout 	<< "Color: " << getEColor() << endl
			<< "Steps: " << getISteps() << endl
			<< "Taken: " << getITaken() << endl
			<< "Lost: " << getILost() << endl
			<< "Active: " << getIActivePawns() << endl
			<< "Roll: " << getIDiceRoll() << endl
			<< "Pawn positions:"
	<< endl;

	// for every pawn
	for (unsigned i = 0; i < m_vPawns.size(); i++)
	{
		// print in the console the position
		cout << "(" << m_vPawns[i]->getIXPosition() << ", " << m_vPawns[i]->getIYPosition() << ") ";
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
	if(iDiceRoll>=1 && iDiceRoll<=6)
		m_iDiceRoll = iDiceRoll;
}

Colors Player::getEColor() const
{
	return m_EColor;
}

int Player::getIFinishPosition() const
{
	return m_iDiceRoll;
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
	for(unsigned i = 0; i < m_vPawns.size(); i++)
	{
		// pass the color
		m_vPawns[i]->setEColor(m_EColor);
	}

}

void Player::SetPawnsVector()
{
	for (unsigned int i = 0; i < PAWNS; i++){
		//make a dynamic allocated pawn
		Pawn* pawn = new Pawn(m_EColor);

		// give it to the vector
		m_vPawns.push_back(pawn);

		// set position into base
		m_vPawns.back()->setIXPosition(BASE_SQUARES[m_EColor-1][i].first);
		m_vPawns.back()->setIYPosition(BASE_SQUARES[m_EColor-1][i].second);
	}
}
