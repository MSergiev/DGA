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
	//Screen constants
	int WIDTH;
	int HEIGHT;
	//Scrollable field constants
	int FIELD_WIDTH;
	int FIELD_HEIGHT;
	///Playing squares count
	int BOARD_LENGTH;
	///Board dimensions
	int BOARD_WIDTH;
	int BOARD_HEIGHT;
	///Square dimensions
	int SQUARE_SIZE;
	///UI button size
	int BUTTON_WIDTH;
	int BUTTON_HEIGHT;
	///Font size
	int FONT_SIZE;
	///Rule screen button params
	int RULES_WIDTH;
	int RULES_HEIGHT;

	///Number of players
	int PLAYERS;
	///Number of pawns
	int PAWNS;
	///Player data amount
	int PLAYER_DATA;
	int MOVEMENT_DELAY;

	///Pawn sprite animation frames
	int PAWN_FRAMES;
	///Sprite sizes (pixels)
	float SPRITE_SCALE[];

	///Win screen data spacing
	int WIN_X_OFF;
	int WIN_Y_OFF;
	int WIN_X_DATA;
	int WIN_Y_DATA;
	int WIN_SHADOW_OFF;
	///UI button vertical offset
	int VERT_OFFSET;

	///Top row leftmost square coordinates
	int ZERO_X_POS;
	int ZERO_Y_POS;
	///Top row leftmost square index
	int ZERO_X_INDEX;
	int ZERO_Y_INDEX;
	///Graphics draw offset
	int X_OFF;
	int Y_OFF;

	///Active board
	bool MOVEABLE_SQUARES[15][15];
	///Next square location in (x,y)
	pair<int, int> NEXT_SQUARE[15][15];
	///Safe squares on board
	pair<int, int> SAFE_SQUARES[3][5];
	///Base squares on board
	pair<int, int> BASE_SQUARES[3][5];

	///Pawn start positions (in game squares)
	unsigned START_POS[];

	///Active squares on board
	pair<int, int> ACTIVE_SQUARES[];
	///Player-specific safe squares direction (x,y)
	pair<int, int> NEXT_SAFE[];
	///Pawn waiting positions (in screen pixels)
	pair<int, int> IDLE_POS[];
	///Final squares on board
	pair<int, int> FINAL_SQUARES[];
	///Start squares on board
	pair<int, int> START_SQUARES[];
	///Safe zone entry points
	pair<int, int> ENTRY_SQUARES[];
	///Pawn positions on square
	pair<int, int> PAWN_LAYOUT[];
	///UI screen coordinates
	pair<int, int> SCREEN_COORDS[];
	///Player dice positions (in pixels)
	pair<int, int> DICE_POS[];

	///UI constants
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
	//UI slider size
	int SLIDER_WIDTH;
	int SLIDER_HEIGHT;
	int KNOB_WIDTH;
	int KNOB_HEIGHT;

	///UI elements location
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

	///Font path
	string FONT_PATH;
	///Pawn sprite path
	string PAWN_PATH;
	///Dice texture path
	string DICE_PATH;
	///Board texture path
	string BOARD_PATH;
	///Scrollable field path
	string SCROLLABLE_PATH;
	///Win screen background path
	string WIN_PATH;
	///Title screen background path
	string TITLE_PATH;
	///Square highlighter path
	string HIGHLIGHTER_PATH;

	///Explosion FX data
	string EXPLODE_PATH;
	int EXPLODE_WIDTH;
	int EXPLODE_HEIGHT;
	int EXPLODE_FRAMES;
	int EXPLODE_DELAY;

	///Shockwave FX data
	string SHOCK_PATH;
	int SHOCK_WIDTH;
	int SHOCK_HEIGHT;
	int SHOCK_FRAMES;
	int SHOCK_DELAY;

public:
	Initialization();
	virtual ~Initialization();

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
	void InitNEXT_SAFE(pugi::xml_node& constants);
	void InitACTIVE_SQUARES(pugi::xml_node& constants);

	void InitSTART_POS(pugi::xml_node& constants);

	void InitMOVEABLE_SQUARES(pugi::xml_node& constants);
	void InitNEXT_SQUARE(pugi::xml_node& constants);
	void InitBASE_SQUARES(pugi::xml_node& constants);
	void InitSAFE_SQUARES(pugi::xml_node& constants);

private:
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
