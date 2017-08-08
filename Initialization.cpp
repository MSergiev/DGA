/*
 * Initialization.cpp
 *
 *  Created on: 4.08.2017 ã.
 *      Author: IVY
 */

#include "Initialization.h"

Initialization::Initialization()
{
	InitializeData();

}

int Initialization::getBoardHeight() const
{
	return BOARD_HEIGHT;
}

void Initialization::setBoardHeight(int boardHeight)
{
	BOARD_HEIGHT = boardHeight;
}

int Initialization::getBoardLength() const
{
	return BOARD_LENGTH;
}

void Initialization::setBoardLength(int boardLength)
{
	BOARD_LENGTH = boardLength;
}

int Initialization::getBoardWidth() const
{
	return BOARD_WIDTH;
}

void Initialization::setBoardWidth(int boardWidth)
{
	BOARD_WIDTH = boardWidth;
}

int Initialization::getButtonHeight() const
{
	return BUTTON_HEIGHT;
}

void Initialization::setButtonHeight(int buttonHeight)
{
	BUTTON_HEIGHT = buttonHeight;
}

int Initialization::getButtonWidth() const
{
	return BUTTON_WIDTH;
}

void Initialization::setButtonWidth(int buttonWidth)
{
	BUTTON_WIDTH = buttonWidth;
}

int Initialization::getFieldHeight() const
{
	return FIELD_HEIGHT;
}

void Initialization::setFieldHeight(int fieldHeight)
{
	FIELD_HEIGHT = fieldHeight;
}

int Initialization::getFieldWidth() const
{
	return FIELD_WIDTH;
}

void Initialization::setFieldWidth(int fieldWidth)
{
	FIELD_WIDTH = fieldWidth;
}

int Initialization::getFontSize() const
{
	return FONT_SIZE;
}

void Initialization::setFontSize(int fontSize)
{
	FONT_SIZE = fontSize;
}

int Initialization::getHeight() const
{
	return HEIGHT;
}

void Initialization::setHeight(int height)
{
	HEIGHT = height;
}

int Initialization::getRulesHeight() const
{
	return RULES_HEIGHT;
}

void Initialization::setRulesHeight(int rulesHeight)
{
	RULES_HEIGHT = rulesHeight;
}

int Initialization::getRulesWidth() const
{
	return RULES_WIDTH;
}

void Initialization::setRulesWidth(int rulesWidth)
{
	RULES_WIDTH = rulesWidth;
}

int Initialization::getSquareSize() const
{
	return SQUARE_SIZE;
}

void Initialization::setSquareSize(int squareSize)
{
	SQUARE_SIZE = squareSize;
}

int Initialization::getWidth() const
{
	return WIDTH;
}

void Initialization::setWidth(int width)
{
	WIDTH = width;
}

Initialization::~Initialization()
{

}

void Initialization::InitializeData()
{
	pugi::xml_document doc;
	pugi::xml_parse_result res = doc.load_file("Constants.xml");

	// checking if the file is loaded
	if (!res)
	{
		// show what is the problem
		cerr << "ERROR with the xml file: " << res.description()
				<< endl;
		return;
	}

	pugi::xml_node constants = doc.first_child();

	// sizes
	pugi::xml_node sizes = constants.first_child();
	setWidth(sizes.child("WIDTH").text().as_int());
	setHeight(sizes.child("HEIGHT").text().as_int());
	setFieldHeight(sizes.child("FIELD_WIDTH").text().as_int());
	setBoardLength(sizes.child("BOARD_LENGTH").text().as_int());
	setBoardWidth(sizes.child("BOARD_WIDTH").text().as_int());
	setBoardHeight(sizes.child("BOARD_HEIGHT").text().as_int());
	setSquareSize(sizes.child("SQUARE_SIZE").text().as_int());
	setButtonWidth(sizes.child("BUTTON_WIDTH").text().as_int());
	setButtonHeight(sizes.child("BUTTON_HEIGHT").text().as_int());
	setFontSize(sizes.child("FONT_SIZE").text().as_int());
	setRulesWidth(sizes.child("RULES_WIDTH").text().as_int());
	setRulesHeight(sizes.child("RULES_HEIGHT").text().as_int());

	// game
	pugi::xml_node game = constants.child("game");
	setPlayers(game.child("PLAYERS").text().as_int());
	setPawns(game.child("PAWNS").text().as_int());
	setPlayerData(game.child("PLAYER_DATA").text().as_int());
	setMovementDelay(game.child("MOVEMENT_DELAY").text().as_int());

	// animation
	pugi::xml_node animation = constants.child("animation");
	setPawnFrames(animation.child("PAWN_FRAMES").text().as_int());

	// spacing
	pugi::xml_node spacing = constants.child("spacing");
	setWinXOff(spacing.child("WIN_X_OFF").text().as_int());
	setWinYOff(spacing.child("WIN_Y_OFF").text().as_int());
	setWinXData(spacing.child("WIN_X_DATA").text().as_int());
	setWinYData(spacing.child("WIN_Y_DATA").text().as_int());
	setWinShadowOff(spacing.child("WIN_SHADOW_OFF").text().as_int());
	setVertOffset(spacing.child("VERT_OFFSET").text().as_int());

	// drawnColors
	pugi::xml_node drawnColors = constants.child("drawnColors");
	pugi::xml_node c_white = drawnColors.child("C_WHITE");
	pugi::xml_attribute_iterator ait = c_white.attributes_begin();
	//setWhite();

	pugi::xml_node c_black = drawnColors.child("C_BLACK");
	pugi::xml_attribute_iterator a = c_black.attributes_begin();

	pugi::xml_node C_RED = drawnColors.child("C_RED");
	pugi::xml_attribute_iterator ai = C_RED.attributes_begin();

	pugi::xml_node C_BLUE = drawnColors.child("C_BLUE");
	pugi::xml_attribute_iterator t = C_BLUE.attributes_begin();

	pugi::xml_node C_GREEN = drawnColors.child("C_GREEN");
	pugi::xml_attribute_iterator aitr = C_GREEN.attributes_begin();

	pugi::xml_node C_YELLOW = drawnColors.child("C_YELLOW");
	pugi::xml_attribute_iterator aitri = C_YELLOW.attributes_begin();

	//enumColors

	// coordinates
	pugi::xml_node coordinates = constants.child("coordinates");
	setZeroXPos(coordinates.child("ZERO_X_POS").text().as_int());
	setZeroYPos(coordinates.child("ZERO_Y_POS").text().as_int());
	setZeroXIndex(coordinates.child("ZERO_X_INDEX").text().as_int());
	setZeroYIndex(coordinates.child("ZERO_Y_INDEX").text().as_int());
	setXOff(coordinates.child("X_OFF").text().as_int());
	setYOff(coordinates.child("Y_OFF").text().as_int());

	//

}

//template<typename T>
int Initialization::InitIntData(int& variable, char* name)
{

	pugi::xml_document doc;
	pugi::xml_parse_result res = doc.load_file("Constants.xml");

// checking if the file is loaded
	if (!res)
	{
		// show what is the problem
		cerr << "ERROR with the xml file: " << res.description()
				<< endl;
	}

	pugi::xml_node constants = doc.first_child();
	pugi::xml_node sizes = constants.first_child();

	string intString = "int";
	string str = "string";

	for (pugi::xml_node constants = constants.first_child();
			constants; constants = constants.next_sibling())
	{
		for (pugi::xml_node size = sizes.first_child(); size; size =
				size.next_sibling())
		{
			if (intString.compare(typeid(variable).name()))
			{
				cout << size.child(name).text().as_int();
				return size.child(name).text().as_int();
			} else
			{
				if (str.compare(typeid(variable).name()))
				{
					//return size.child(name).text().as_string();
				}
			}
		}
	}
}

int Initialization::getMovementDelay() const
{
	return MOVEMENT_DELAY;
}

void Initialization::setMovementDelay(int movementDelay)
{
	MOVEMENT_DELAY = movementDelay;
}

int Initialization::getPawns() const
{
	return PAWNS;
}

void Initialization::setPawns(int pawns)
{
	PAWNS = pawns;
}

int Initialization::getPlayerData() const
{
	return PLAYER_DATA;
}

void Initialization::setPlayerData(int playerData)
{
	PLAYER_DATA = playerData;
}

int Initialization::getPlayers() const
{
	return PLAYERS;
}

int Initialization::getPawnFrames() const
{
	return PAWN_FRAMES;
}

int Initialization::getVertOffset() const
{
	return VERT_OFFSET;
}

void Initialization::setVertOffset(int vertOffset)
{
	VERT_OFFSET = vertOffset;
}

int Initialization::getWinShadowOff() const
{
	return WIN_SHADOW_OFF;
}

void Initialization::setWinShadowOff(int winShadowOff)
{
	WIN_SHADOW_OFF = winShadowOff;
}

int Initialization::getWinXData() const
{
	return WIN_X_DATA;
}

void Initialization::setWinXData(int winXData)
{
	WIN_X_DATA = winXData;
}

int Initialization::getWinXOff() const
{
	return WIN_X_OFF;
}

void Initialization::setWinXOff(int winXOff)
{
	WIN_X_OFF = winXOff;
}

int Initialization::getWinYData() const
{
	return WIN_Y_DATA;
}

void Initialization::setWinYData(int winYData)
{
	WIN_Y_DATA = winYData;
}

int Initialization::getWinYOff() const
{
	return WIN_Y_OFF;
}

SDL_Color Initialization::getBlack() const
{
	return C_BLACK;
}

void Initialization::setBlack(SDL_Color black)
{
	C_BLACK = black;
}

SDL_Color Initialization::getBlue() const
{
	return C_BLUE;
}

void Initialization::setBlue(SDL_Color blue)
{
	C_BLUE = blue;
}

SDL_Color Initialization::getGreen() const
{
	return C_GREEN;
}

void Initialization::setGreen(SDL_Color green)
{
	C_GREEN = green;
}

SDL_Color Initialization::getRed() const
{
	return C_RED;
}

void Initialization::setRed(SDL_Color red)
{
	C_RED = red;
}

SDL_Color Initialization::getWhite() const
{
	return C_WHITE;
}

void Initialization::setWhite(SDL_Color white)
{
	C_WHITE = white;
}

SDL_Color Initialization::getYellow() const
{
	return C_YELLOW;
}

int Initialization::getXOff() const
{
	return X_OFF;
}

void Initialization::setXOff(int off)
{
	X_OFF = off;
}

int Initialization::getYOff() const
{
	return Y_OFF;
}

void Initialization::setYOff(int off)
{
	Y_OFF = off;
}

int Initialization::getZeroXIndex() const
{
	return ZERO_X_INDEX;
}

void Initialization::setZeroXIndex(int zeroXIndex)
{
	ZERO_X_INDEX = zeroXIndex;
}

int Initialization::getZeroXPos() const
{
	return ZERO_X_POS;
}

void Initialization::setZeroXPos(int zeroXPos)
{
	ZERO_X_POS = zeroXPos;
}

int Initialization::getZeroYIndex() const
{
	return ZERO_Y_INDEX;
}

void Initialization::setZeroYIndex(int zeroYIndex)
{
	ZERO_Y_INDEX = zeroYIndex;
}

int Initialization::getZeroYPos() const
{
	return ZERO_Y_POS;
}

int Initialization::getControlsQuit() const
{
	return CONTROLS_QUIT;
}

void Initialization::setControlsQuit(int controlsQuit)
{
	CONTROLS_QUIT = controlsQuit;
}

int Initialization::getControlsRules() const
{
	return CONTROLS_RULES;
}

void Initialization::setControlsRules(int controlsRules)
{
	CONTROLS_RULES = controlsRules;
}

int Initialization::getControlsSound() const
{
	return CONTROLS_SOUND;
}

void Initialization::setControlsSound(int controlsSound)
{
	CONTROLS_SOUND = controlsSound;
}

int Initialization::getFadeFactor() const
{
	return FADE_FACTOR;
}

void Initialization::setFadeFactor(int fadeFactor)
{
	FADE_FACTOR = fadeFactor;
}

int Initialization::getKnobHeight() const
{
	return KNOB_HEIGHT;
}

void Initialization::setKnobHeight(int knobHeight)
{
	KNOB_HEIGHT = knobHeight;
}

int Initialization::getKnobWidth() const
{
	return KNOB_WIDTH;
}

void Initialization::setKnobWidth(int knobWidth)
{
	KNOB_WIDTH = knobWidth;
}

int Initialization::getRulesBack() const
{
	return RULES_BACK;
}

void Initialization::setRulesBack(int rulesBack)
{
	RULES_BACK = rulesBack;
}

int Initialization::getRulesNext() const
{
	return RULES_NEXT;
}

void Initialization::setRulesNext(int rulesNext)
{
	RULES_NEXT = rulesNext;
}

int Initialization::getSliderHeight() const
{
	return SLIDER_HEIGHT;
}

void Initialization::setSliderHeight(int sliderHeight)
{
	SLIDER_HEIGHT = sliderHeight;
}

int Initialization::getSliderWidth() const
{
	return SLIDER_WIDTH;
}

void Initialization::setSliderWidth(int sliderWidth)
{
	SLIDER_WIDTH = sliderWidth;
}

int Initialization::getTitleContinue() const
{
	return TITLE_CONTINUE;
}

void Initialization::setTitleContinue(int titleContinue)
{
	TITLE_CONTINUE = titleContinue;
}

int Initialization::getTitleQuit() const
{
	return TITLE_QUIT;
}

void Initialization::setTitleQuit(int titleQuit)
{
	TITLE_QUIT = titleQuit;
}

int Initialization::getTitleStart() const
{
	return TITLE_START;
}

void Initialization::setTitleStart(int titleStart)
{
	TITLE_START = titleStart;
}

int Initialization::getWinQuit() const
{
	return WIN_QUIT;
}

void Initialization::setWinQuit(int winQuit)
{
	WIN_QUIT = winQuit;
}

int Initialization::getWinRestart() const
{
	return WIN_RESTART;
}

void Initialization::setWinRestart(int winRestart)
{
	WIN_RESTART = winRestart;
}

void Initialization::setZeroYPos(int zeroYPos)
{
	ZERO_Y_POS = zeroYPos;
}

void Initialization::setYellow(SDL_Color yellow)
{
	C_YELLOW = yellow;
}

void Initialization::setWinYOff(int winYOff)
{
	WIN_Y_OFF = winYOff;
}

void Initialization::setPawnFrames(int pawnFrames)
{
	PAWN_FRAMES = pawnFrames;
}

void Initialization::setPlayers(int players)
{
	PLAYERS = players;
}

const char* Initialization::makeChar(char name[])
{
	char* n = name;
	return n;
}
