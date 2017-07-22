/*
 * WinScreen.cpp
 *
 *  Created on: 17.07.2017 ã.
 *      Author: IVY
 */

#include "WinScreen.h"

WinScreen::WinScreen()
{
	for(int i = 0; i < PLAYERS; i++)
	{
		for (int j = 0; j < PLAYER_DATA; j++) {
			m_sPlayerData[i][j] = "";
		}
	}
}

WinScreen::~WinScreen()
{
	// TODO Auto-generated destructor stub
}

void WinScreen::init()
{
	m_bRestart.setTexture(RESTART_PATH);
	m_BQuit.setTexture(QUIT_PATH);

	m_bRestart.setSFX(BUTTON_SFX);
	m_BQuit.setSFX(BUTTON_SFX);

	m_bRestart.setLocation((WIDTH-BUTTON_WIDTH)/2, HEIGHT-VERT_OFFSET-2*BUTTON_HEIGHT);
	m_BQuit.setLocation((WIDTH-BUTTON_WIDTH)/2, HEIGHT-VERT_OFFSET);

	m_bRestart.setSize(BUTTON_WIDTH, BUTTON_HEIGHT);
	m_BQuit.setSize(BUTTON_WIDTH, BUTTON_HEIGHT);

	UI::loadBackground(WIN_PATH);
}

void WinScreen::render()
{
//	UI::render();
	m_bRestart.render();
	m_BQuit.render();

	//Text render color
	SDL_Color textColor C_WHITE;
	
	for(int i = 0; i < PLAYERS; i++)
	{
		for(int j = 0; j < PLAYER_DATA; j++)
		{
			text.textLoad(m_sPlayerData[i][j], getFont(), textColor);
			text.render(100+j*WIN_OFFSET,100+i*WIN_OFFSET);
		}
	}
}

int WinScreen::eventHandler(SDL_Event& e)
{
	int ButtonState = 0;

	ButtonState |= m_bRestart.isClicked(e);
	ButtonState <<= 1;
	ButtonState |= m_BQuit.isClicked(e);

	return ButtonState;
}

string WinScreen::ColorToString(Colors color)
{
	switch (color)
	{
	case BLUE:
		return "Blue";
		break;

	case YELLOW:
		return "Yellow";
		break;

	case RED:
		return "Red";
		break;

	default:
		return "None";
		break;
	}
}

void WinScreen::loadData(deque<Player*> data)
{
	stringstream str;
	for (unsigned int i = 0; i < data.size(); i++)
	{
		str << data[i]->getIFinishPosition();
		m_sPlayerData[i][0] = str.str();
		str.str("");
		str	<< ColorToString(data[i]->getEColor());
		m_sPlayerData[i][1] = str.str();
		str.str("");
		str	<< data[i]->getISteps();
		m_sPlayerData[i][2] = str.str();
		str.str("");
		str	<< data[i]->getITaken();
		m_sPlayerData[i][3] = str.str();
		str.str("");
		str	<< data[i]->getILost();
		m_sPlayerData[i][4] = str.str();
		str.str("");
	}
}
