#include "Player.h"

Player::Player(Colors color)
		: m_iSteps(), m_iTaken(), m_iHadTaken()
{
	setEColor(color);
	SetPawnsVector();
	setIActivePawns(0);
	setIDiceRoll(1);
}


Player::~Player()
{
	for (unsigned int i = 0; i < m_vPawns.size(); i++)
	{
		m_vPawns[i] = NULL;
		delete m_vPawns[i];
	}
}

void Player::SetRenderer(SDL_Renderer* renderer)
{
	for (unsigned int i = 0; i < m_vPawns.size(); i++)
	{
		m_vPawns[i]->setRenderer(renderer);
	}
}

void Player::Render(int x, int y)
{
	for (unsigned int i = 0; i < m_vPawns.size(); i++)
	{
		m_vPawns[i]->render(x, y);
	}
}

void Player::Print()
{
	cout 	<< "Color: " << getEColor() << endl
			<< "Steps: " << getISteps() << endl
			<< "Taken: " << getITaken() << endl
			<< "Had taken: " << getIHadTaken() << endl
	<< endl;
}

vector<int> Player::GetPositions()
{
	vector <int> result;
	for (unsigned int i = 0; i < m_vPawns.size(); i++){
		result[i] = m_vPawns[i]->getUiPosition();
	}

	return result;
}

// setters and getters
int Player::getIHadTaken() const
{
	return m_iHadTaken;
}

void Player::setIHadTaken(int iHadTaken)
{
	m_iHadTaken = iHadTaken;
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

void Player::setEColor(Colors eColor)
{
	m_EColor = eColor;
}

const vector<Pawn*>& Player::getVPawns() const
{
	return m_vPawns;
}

void Player::SetPawnsVector()
{
	Pawn* pawn = new Pawn;
	pawn->setEColor(getEColor());
	for (unsigned int i = 0; i < 5; i++){
		m_vPawns.push_back(pawn);
	}
}
