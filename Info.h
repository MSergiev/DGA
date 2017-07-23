/*
 * Info.h
 *
 *  Created on: Jul 19, 2017
 *      Author: Puzz
 */

#ifndef INFO_H_
#define INFO_H_

#define PAGES_NUM 2

#include "UI.h"

class Info: public UI {
public:
	Info();
	virtual ~Info();
	void init();
	virtual int eventHandler(SDL_Event& e);
	virtual void fadeIn();
	virtual void fadeOut();
	virtual void render();
private:
int PageCounter;
Texture pages[PAGES_NUM];
Button pageNext;
Button pageBack;
};

#endif /* INFO_H_ */
