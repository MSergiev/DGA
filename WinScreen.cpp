/*
 * WinScreen.cpp
 *
 *  Created on: 17.07.2017 ã.
 *      Author: IVY
 */

#include "WinScreen.h"

WinScreen::WinScreen()
{
}

WinScreen::~WinScreen()
{
	// TODO Auto-generated destructor stub
}

void WinScreen::init()
{
	SDL_Color button { 255, 255, 255, 0 };
	UI::loadFont(FONT_PATH, 12);

	m_bRestart.setRenderer(UI::getRenderer());
	m_BQuit.setRenderer(UI::getRenderer());

	m_bRestart.setLabel("RESTART", UI::getFont(), button);
	m_BQuit.setLabel("QUIT", UI::getFont(), button);

	m_bRestart.setLocation(400, 300);
	m_BQuit.setLocation(400, 500);

	m_bRestart.setSize(100, 100);
	m_BQuit.setSize(100, 100);

	UI::loadBackground("./GFX/Untitled.png");
}

void WinScreen::render()
{
	UI::render();
	m_bRestart.render();
	m_BQuit.render();
	text.render(100,100);
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
		str << setw(6) << (i + 1) <<
			ColorToString(data[i]->getEColor()) <<
			data[i]->getISteps() <<
			data[i]->getITaken() <<
			data[i]->getILost() << endl;
	}
	SDL_Color textColor { 255, 255, 255, 0 };
	text.textLoad(str.str(), mFont, textColor);
}
