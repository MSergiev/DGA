/*
 * WinScreen.h
 *
 *  Created on: 17.07.2017 ã.
 *      Author: IVY
 */

#ifndef WINSCREEN_H_
#define WINSCREEN_H_

#include "UI.h"
#include "Player.h"
#include <deque>
#include <sstream>
#include <iomanip>
using std::deque;
using std::stringstream;
using std::setw;
using std::left;

class WinScreen: public UI
{
private:
	// button restart
	Button m_bRestart;
	// button quit
	Button m_BQuit;
	// text that will be shown in the screen
	Texture text;
	//String array to hold each individual player data
	string m_sPlayerData[PLAYERS][PLAYER_DATA];

	// private method for transferring the data
	// of the enum value to a string variable
	string ColorToString(Colors color);

public:
	WinScreen();
	virtual ~WinScreen();

	// the initialize method for every data of the screen
	void init();

	// the render method which overrides the parent render method
	virtual void render();

	// the event handler for the page
	// which implements the parent abstract eventHandler method
	virtual int eventHandler(SDL_Event& e);

	// loads the data from the deque of players
	// and puts the data into the string array of the data
	// which will be shown to the screen
	void loadData(deque<Player*>);
};

#endif /* WINSCREEN_H_ */
