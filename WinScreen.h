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
	Button m_bRestart;
	Button m_BQuit;
	Texture text;
	///String array to hold each individual player data
	string m_sPlayerData[PLAYERS][PLAYER_DATA];

	/// private color
	string ColorToString(Colors color);

public:
	WinScreen();
	virtual ~WinScreen();

	void init();
	virtual void render();
	virtual int eventHandler(SDL_Event& e);
	virtual void fadeIn();
	virtual void fadeOut();
	void loadData(deque<Player*>);
};

#endif /* WINSCREEN_H_ */
