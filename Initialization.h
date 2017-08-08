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
	float SPRITE_SCALE[];

	int WIN_X_OFF;
	int WIN_Y_OFF;
	int WIN_X_DATA;
	int WIN_Y_DATA;
	int WIN_SHADOW_OFF;
	int VERT_OFFSET;

	int ZERO_X_POS;
	int ZERO_Y_POS;
	int ZERO_X_INDEX;
	int ZERO_Y_INDEX;
	int X_OFF;
	int Y_OFF;

	//pair<int, int> BASE_SQUARES[][];

	unsigned START_POS[];

	pair<int, int> IDLE_POS[];
	pair<int, int> FINAL_SQUARES[];
	pair<int, int> START_SQUARES[];
	pair<int, int> ENTRY_SQUARES[];
	pair<int, int> PAWN_LAYOUT[];
	pair<int, int> SCREEN_COORDS[];
	pair<int, int> DICE_POS[];

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

	string START_PATH;
	string RESTART_PATH;
	string CONTINUE_PATH;
	string QUIT_PATH;
	string SOUND_ON_PATH;
	string SOUND_OFF_PATH;
	string RULES_PATH;
	string SFX_SLIDER_PATH;
	string BGM_SLIDER_PATH;
	string SLIDER_KNOB_PATH;

	string FONT_PATH;
	string PAWN_PATH;
	string DICE_PATH;
	string BOARD_PATH;
	string SCROLLABLE_PATH;
	string WIN_PATH;
	string TITLE_PATH;
	string HIGHLIGHTER_PATH;

	string EXPLODE_PATH;
	int EXPLODE_WIDTH;
	int EXPLODE_HEIGHT;
	int EXPLODE_FRAMES;
	int EXPLODE_DELAY;

	string SHOCK_PATH;
	int SHOCK_WIDTH;
	int SHOCK_HEIGHT;
	int SHOCK_FRAMES;
	int SHOCK_DELAY;

private:
	// method which initialize shared constants
	void InitializeData();

	// helper methods which initialized
	// the different nodes of the xml
	void InitSizes(pugi::xml_node &);
	void InitGame(pugi::xml_node &);
	void InitAnimation(pugi::xml_node &);
	void InitSpacing(pugi::xml_node &);
	void InitCoordinates(pugi::xml_node&);
	void InitUI_CONSTANTS(pugi::xml_node &);

	void InitUI_ELEMENTS_PATHS(pugi::xml_node &);
	void InitBASIC_PATHS(pugi::xml_node &);

	void InitExplosion_FX_DATA(pugi::xml_node &);
	void InitShockwave_FX_DATA(pugi::xml_node &);

	void InitDicePos(pugi::xml_node &);
	void InitSCREEN_COORDS(pugi::xml_node&);
	void InitPAWN_LAYOUT(pugi::xml_node&);
	void InitENTRY_SQUARES(pugi::xml_node&);
	void InitSTART_SQUARES(pugi::xml_node&);
	void InitFINAL_SQUARES(pugi::xml_node& constants);
	void InitIDLE_POS(pugi::xml_node& constants);

	void InitSTART_POS(pugi::xml_node& constants);

	void InitBASE_SQUARES(pugi::xml_node& constants);

public:
	Initialization();
	virtual ~Initialization();

	// setters
	void setBoardHeight(int boardHeight);

	void setBoardLength(int boardLength);

	void setBoardWidth(int boardWidth);

	void setButtonHeight(int buttonHeight);

	void setButtonWidth(int buttonWidth);

	void setFieldHeight(int fieldHeight);

	void setFieldWidth(int fieldWidth);

	void setFontSize(int fontSize);

	void setHeight(int height);

	void setRulesHeight(int rulesHeight);

	void setRulesWidth(int rulesWidth);

	void setSquareSize(int squareSize);

	void setWidth(int width);

	void setMovementDelay(int movementDelay);

	void setPawns(int pawns);

	void setPlayerData(int playerData);

	void setPlayers(int players);

	void setPawnFrames(int pawnFrames);

	void setVertOffset(int vertOffset);

	void setWinShadowOff(int winShadowOff);

	void setWinXData(int winXData);

	void setWinXOff(int winXOff);

	void setWinYData(int winYData);

	void setWinYOff(int winYOff);

	void setYOff(int off);

	void setXOff(int off);

	void setZeroXIndex(int zeroXIndex);

	void setZeroXPos(int zeroXPos);

	void setZeroYIndex(int zeroYIndex);

	void setZeroYPos(int zeroYPos);

	void setControlsQuit(int controlsQuit);

	void setControlsRules(int controlsRules);

	void setControlsSound(int controlsSound);

	void setFadeFactor(int fadeFactor);

	void setKnobHeight(int knobHeight);

	void setKnobWidth(int knobWidth);

	void setRulesBack(int rulesBack);

	void setRulesNext(int rulesNext);

	void setSliderHeight(int sliderHeight);

	void setSliderWidth(int sliderWidth);

	void setTitleContinue(int titleContinue);

	void setTitleQuit(int titleQuit);

	void setTitleStart(int titleStart);

	void setWinQuit(int winQuit);

	void setWinRestart(int winRestart);

	void setBgmSliderPath(const string& bgmSliderPath);

	void setContinuePath(const string& continuePath);

	void setQuitPath(const string& quitPath);

	void setRestartPath(const string& restartPath);

	void setRulesPath(const string& rulesPath);

	void setSfxSliderPath(const string& sfxSliderPath);

	void setSliderKnobPath(const string& sliderKnobPath);

	void setSoundOffPath(const string& soundOffPath);

	void setSoundOnPath(const string& soundOnPath);

	void setStartPath(const string& startPath);

	void setBoardPath(const string& boardPath);

	void setDicePath(const string& dicePath);

	void setFontPath(const string& fontPath);

	void setHighlighterPath(const string& highlighterPath);

	void setPawnPath(const string& pawnPath);

	void setScrollablePath(const string& scrollablePath);

	void setTitlePath(const string& titlePath);

	void setWinPath(const string& winPath);

	void setExplodeDelay(int explodeDelay);

	void setExplodeFrames(int explodeFrames);

	void setExplodeHeight(int explodeHeight);

	void setExplodePath(const string& explodePath);

	void setExplodeWidth(int explodeWidth);

	void setShockDelay(int shockDelay);

	void setShockFrames(int shockFrames);

	void setShockHeight(int shockHeight);

	void setShockPath(const string& shockPath);

	void setShockWidth(int shockWidth);
};

#endif /* INITIALIZATION_H_ */
