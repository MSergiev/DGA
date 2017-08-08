/*
 * Initialization.h
 *
 *  Created on: 4.08.2017 ã.
 *      Author: IVY
 */

#ifndef INITIALIZATION_H_
#define INITIALIZATION_H_

#include "pugixml.hpp"
#include "Shared.h"

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
public:
	int WIDTH;
	int HEIGHT;
	int FIELD_WIDTH;
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

	int PLAYERS;
	int PAWNS;
	int PLAYER_DATA;
	int MOVEMENT_DELAY;

	int PAWN_FRAMES;

	int WIN_X_OFF;
	int WIN_Y_OFF;
	int WIN_X_DATA;
	int WIN_Y_DATA;
	int WIN_SHADOW_OFF;
	int VERT_OFFSET;

	SDL_Color C_WHITE;
	SDL_Color C_BLACK;
	SDL_Color C_RED;
	SDL_Color C_BLUE;
	SDL_Color C_GREEN;
	SDL_Color C_YELLOW;

	int ZERO_X_POS;
	int ZERO_Y_POS;
	int ZERO_X_INDEX;
	int ZERO_Y_INDEX;
	int X_OFF;
	int Y_OFF;

	int TITLE_START;
	int TITLE_CONTINUE;
	int TITLE_QUIT;
	int WIN_RESTART;
	int WIN_QUIT;
	int CONTROLS_SOUND;
	int CONTROLS_RULES;
	int CONTROLS_QUIT;
	int RULES_BACK;
	int RULES_NEXT;
	int FADE_FACTOR;
	int SLIDER_WIDTH;
	int SLIDER_HEIGHT;
	int KNOB_WIDTH;
	int KNOB_HEIGHT;

private:
	void InitializeData();

public:
	Initialization();
	virtual ~Initialization();

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

	int getFieldWidth() const;
	void setFieldWidth(int fieldWidth);

	int getFontSize() const;
	void setFontSize(int fontSize);

	int getHeight() const;
	void setHeight(int height);

	int getRulesHeight() const;
	void setRulesHeight(int rulesHeight);

	int getRulesWidth() const;
	void setRulesWidth(int rulesWidth);

	int getSquareSize() const;
	void setSquareSize(int squareSize);

	int getWidth() const;
	void setWidth(int width);

	// tried to make a template function
	// which can init int and string data
	//template<typename T>
	int InitIntData(int &variable, char* name);

	const char * makeChar(char[]);

	int getMovementDelay() const;
	void setMovementDelay(int movementDelay);

	int getPawns() const;
	void setPawns(int pawns);

	int getPlayerData() const;
	void setPlayerData(int playerData);

	int getPlayers() const;
	void setPlayers(int players);
	int getPawnFrames() const;
	void setPawnFrames(int pawnFrames);
	int getVertOffset() const;
	void setVertOffset(int vertOffset);
	int getWinShadowOff() const;
	void setWinShadowOff(int winShadowOff);
	int getWinXData() const;
	void setWinXData(int winXData);
	int getWinXOff() const;
	void setWinXOff(int winXOff);
	int getWinYData() const;
	void setWinYData(int winYData);
	int getWinYOff() const;
	void setWinYOff(int winYOff);
	SDL_Color getBlack() const;
	void setBlack(SDL_Color black);
	SDL_Color getBlue() const;
	void setBlue(SDL_Color blue);
	SDL_Color getGreen() const;
	void setGreen(SDL_Color green);
	SDL_Color getRed() const;
	void setRed(SDL_Color red);
	SDL_Color getWhite() const;
	void setWhite(SDL_Color white);
	SDL_Color getYellow() const;
	void setYellow(SDL_Color yellow);
	int getYOff() const;
	void setYOff(int off);
	int getXOff() const;
	void setXOff(int off);
	int getZeroXIndex() const;
	void setZeroXIndex(int zeroXIndex);
	int getZeroXPos() const;
	void setZeroXPos(int zeroXPos);
	int getZeroYIndex() const;
	void setZeroYIndex(int zeroYIndex);
	int getZeroYPos() const;
	void setZeroYPos(int zeroYPos);
	int getControlsQuit() const;
	void setControlsQuit(int controlsQuit);
	int getControlsRules() const;
	void setControlsRules(int controlsRules);
	int getControlsSound() const;
	void setControlsSound(int controlsSound);
	int getFadeFactor() const;
	void setFadeFactor(int fadeFactor);
	int getKnobHeight() const;
	void setKnobHeight(int knobHeight);
	int getKnobWidth() const;
	void setKnobWidth(int knobWidth);
	int getRulesBack() const;
	void setRulesBack(int rulesBack);
	int getRulesNext() const;
	void setRulesNext(int rulesNext);
	int getSliderHeight() const;
	void setSliderHeight(int sliderHeight);
	int getSliderWidth() const;
	void setSliderWidth(int sliderWidth);
	int getTitleContinue() const;
	void setTitleContinue(int titleContinue);
	int getTitleQuit() const;
	void setTitleQuit(int titleQuit);
	int getTitleStart() const;
	void setTitleStart(int titleStart);
	int getWinQuit() const;
	void setWinQuit(int winQuit);
	int getWinRestart() const;
	void setWinRestart(int winRestart);
};

#endif /* INITIALIZATION_H_ */
