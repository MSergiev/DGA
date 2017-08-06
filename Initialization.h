/*
 * Initialization.h
 *
 *  Created on: 4.08.2017 ã.
 *      Author: IVY
 */

#ifndef INITIALIZATION_H_
#define INITIALIZATION_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#include "pugixml.hpp"

#include <iostream>
#include <string>
#include <typeinfo>
#include <stdio.h>
using std::cout;
using std::endl;
using std::pair;
using std::string;
using std::cerr;

class Initialization
{
private:
	int width;
	int height;
	int fw;
	int FIELD_HEIGHT;
	int BOARD_LENGTH;
	int BOARD_WIDTH;
	int BOARD_HEIGHT;
	int SQUARE_SIZE;
	int BUTTON_WIDTH;
	int BUTTON_HEIGHT;
	int FONT_SIZE;
	int RULES_WIDTH;
	int RULES_HEIGHT;

	void setWidth(int width);
	void InitializeData();

public:
	Initialization();
	virtual ~Initialization();

	int getWidth() const;

	int getHeight() const;
	void setHeight(int height);

	int getBoardHeight() const;
	void setBoardHeight(int boardHeight);

	int getBoardLength() const;
	void setBoardLength(int boardLength);

	int getBoardWidth() const;
	void setBoardWidth(int boardWidth);

	int getButtonHeight() const;
	void setButtonHeight(int buttonHeight);

	int getButtonWidth() const;
	void setButtonWidth(int buttonWidth);

	int getFieldHeight() const;
	void setFieldHeight(int fieldHeight);

	int getFontSize() const;
	void setFontSize(int fontSize);

	int getFw() const;
	void setFw(int fw);

	int getRulesHeight() const;
	void setRulesHeight(int rulesHeight);

	int getRulesWidth() const;
	void setRulesWidth(int rulesWidth);

	int getSquareSize() const;
	void setSquareSize(int squareSize);

	// tried to make a template function
	// which can init int and string data
	template<typename T>
	int InitIntData(int variable, const char* name);
};

#endif /* INITIALIZATION_H_ */
