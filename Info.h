/*
 * Info.h
 *
 *  Created on: Jul 19, 2017
 *      Author: Puzz
 */

#ifndef INFO_H_
#define INFO_H_

#include "UI.h"

class Info: public UI {
public:
	Info();
	virtual ~Info();
	void init();
	virtual int eventHandler(SDL_Event& e);
	virtual void render();
private:
int PageCounter=0;
const int NumberOfPages;
Texture pages[];
Button pageNext;
Button pageBack;
};

#endif /* INFO_H_ */
