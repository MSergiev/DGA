#include "Player.h"

Player::Player(Colors color)
		: m_iSteps(), m_iTaken(), m_iLost()
{
	SetPawnsVector();
	setIActivePawns(0);
	setIDiceRoll(1);
	setIFinishPosition(0);
	setEColor(color);
}


Player::~Player()
{
	for (unsigned int i = 0; i < m_vPawns.size(); i++)
	{
		delete m_vPawns[i];
		m_vPawns[i] = NULL;
	}
}

void Player::SetRenderer(SDL_Renderer* renderer)
{
	for (unsigned int i = 0; i < m_vPawns.size(); i++)
	{
		m_vPawns[i]->setRenderer(renderer);
	}
}

void Player::Render(vector<pair<int, int> > pos)
{
	for (unsigned int i = 0; i < pos.size(); i++)
	{
		m_vPawns[i]->render(pos[i].first, pos[i].second);
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
	for (unsigned i = 0; i < m_vPawns.size(); i++)
	{
		cout << m_vPawns[i]->getIPosition() << " ";
	}
	cout << endl;
}

vector<int> Player::GetPositions()
{
	vector <int> result;
	for (unsigned int i = 0; i < m_vPawns.size(); i++){
		result[i] = m_vPawns[i]->getIPosition();
	}

	return result;
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

int Player::getFinishPosition() const
{
	return m_iDiceRoll;
}

void Player::setIFinishPosition(int iFinishPosition)
{
	m_iFinishPosition = iFinishPosition;
}

Colors Player::getEColor() const
{
	return m_EColor;
}

void Player::setEColor(Colors eColor)
{
	m_EColor = eColor;
	for(unsigned i = 0; i < m_vPawns.size(); i++)
	{
		m_vPawns[i]->setEColor(m_EColor);
	}

}

void Player::SetPawnsVector()
{
	for (unsigned int i = 0; i < PAWNS; i++){
		Pawn* pawn = new Pawn;
		m_vPawns.push_back(pawn);
	}
}
