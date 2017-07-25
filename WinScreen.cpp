/*
 * WinScreen.cpp
 *
 *  Created on: 17.07.2017 ã.
 *      Author: IVY
 */

#include "WinScreen.h"

WinScreen::WinScreen()
{
	// for each player
	for(int i = 0; i < PLAYERS; i++)
	{
		// Initialize with the empty string for the data
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
	// load the textures for the buttons
	m_bRestart.setTexture(RESTART_PATH);
	m_BQuit.setTexture(QUIT_PATH);

	// set the music for the buttons
	m_bRestart.setSFX(BUTTON_SFX);
	m_BQuit.setSFX(BUTTON_SFX);

	// load the textures in the right location
	m_bRestart.setLocation((WIDTH-BUTTON_WIDTH)/2, HEIGHT-VERT_OFFSET-2*BUTTON_HEIGHT);
	m_BQuit.setLocation((WIDTH-BUTTON_WIDTH)/2, HEIGHT-VERT_OFFSET);

	// set the size on the buttons
	m_bRestart.setSize(BUTTON_WIDTH, BUTTON_HEIGHT);
	m_BQuit.setSize(BUTTON_WIDTH, BUTTON_HEIGHT);
}

void WinScreen::render()
{
	// render the buttons
	m_bRestart.render();
	m_BQuit.render();

	//Text render color
	SDL_Color textColor C_WHITE;
	//Text shadow color
	SDL_Color textShadow C_BLACK;
	// for each player
	for(int i = 0; i < PLAYERS; i++)
	{
		// and pawn
		for(int j = 0; j < PLAYER_DATA; j++)
		{
			// load the text from the data with black color
			text.textLoad(m_sPlayerData[i][j], getFont(), textShadow);
			// and render as shadow
			text.render(WIN_X_OFF+j*WIN_X_DATA+WIN_SHADOW_OFF, WIN_Y_OFF+i*WIN_Y_DATA+WIN_SHADOW_OFF);
			
			// load the text from the data
			text.textLoad(m_sPlayerData[i][j], getFont(), textColor);
			// and render it
			text.render(WIN_X_OFF+j*WIN_X_DATA, WIN_Y_OFF+i*WIN_Y_DATA);
		}
	}
}

// overridden animations
void WinScreen::fadeIn(){
	m_bRestart.fadeIn(FADE_FACTOR);
	m_BQuit.fadeIn(FADE_FACTOR);
}
void WinScreen::fadeOut(){
	m_bRestart.fadeOut(FADE_FACTOR);
	m_BQuit.fadeOut(FADE_FACTOR);
}

int WinScreen::eventHandler(SDL_Event& e)
{
	// make a variable which will be returned
	int ButtonState = 0;

	// check if enough time has passed
	if(UI::debounce()){
	// Assign the variable after changing the value with logical or
	// on the value of the integer with the returned value
	// of method on the restart button responsible for checking
	// the state (clicked or not) of the button
	ButtonState |= m_bRestart.isClicked(e);
	// than shift the bits in the variable to make room for the other value
	ButtonState <<= 1;
	// do the same thing with the quit button
	ButtonState |= m_BQuit.isClicked(e);

	}
	// than return the variable with the correct arranged data
	return ButtonState;
}

string WinScreen::ColorToString(Colors color)
{
	// check the value of the Colors enum variable
	switch (color)
	{
	// and return a string with the correct color
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
	// make a stringstream variable in which
	// we are going to fill the data for the players
	// so we can put it in the private array of player data
	stringstream str;

	// for each player
	for (unsigned int i = 0; i < data.size(); i++)
	{
		// get all the data
		str << data[i]->getIFinishPosition();
		// and put it to the private member string array
		// arranged by player - data
		m_sPlayerData[i][0] = str.str();
		// delete the previous data so the next data
		// will be saved properly
		str.str("");

		// do that for each piece of data
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
