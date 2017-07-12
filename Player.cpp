#include "Player.h"

Player::Player()
		:  m_strColor(), m_iSteps(), m_iTaken(), m_iHadTaken()
{
	setIPlayerPosition(1);
}

Player::~Player()
{
	for (unsigned int i = 0; i < m_vPawns.size(); i++)
	{
		m_vPawns[i] = NULL;
		delete m_vPawns[i];
	}
}

void Player::render()
{
	for (unsigned int i = 0; i < m_vPawns.size(); i++)
	{
		m_vPawns[i]->render();
	}
}

void Player::print()
{
	cout 	<< "Player's position: " << getIPlayerPosition() << endl
			<< "Color: " << getStrColor() << endl
			<< "Steps: " << getISteps() << endl
			<< "Taken: " << getITaken() << endl
			<< "Had taken: " << getIHadTaken() << endl
	<< endl;
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

int Player::getIPlayerPosition() const
{
	return m_iPlayerPosition;
}

void Player::setIPlayerPosition(int iPlayerPosition)
{
	m_iPlayerPosition = iPlayerPosition;
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

const string& Player::getStrColor() const
{
	return m_strColor;
}

void Player::setStrColor(const string& strColor)
{
	m_strColor = strColor;
}

