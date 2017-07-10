#include "Player.h"

Player::Player()
		: m_iPlayerPosition(), m_strColor(), m_iSteps(), m_iTaken(), m_iHadTaken()
{
	//Initialize frame dimensions
//	SDL_Rect frame = { 0, 0, SPRITE_SIZE, SPRITE_SIZE };
	//Create sprite object
//	mPlayerSprite = new Sprite(frame, NUM_OF_FRAMES, ANIMATION_DELAY);
}

Player::~Player()
{
	//Release resources
	//mPlayerSprite->free();
	//delete mPlayerSprite;
}

void Player::render(int x, int y)
{
	//Render sprite
//	mPlayerSprite->render(x, y);
}

void Player::setRenderer(SDL_Renderer* renderer)
{
//	mPlayerSprite->setRenderer(renderer);
	//mPlayerSprite->load("./GFX/bomb.png");
}

void Player::print()
{
	cout << "Player's position: " << getIPlayerPosition() << endl
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

