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

Initialization::~Initialization()
{

}

void Initialization::InitSizes(pugi::xml_node& constants)
{
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
}

void Initialization::InitGame(pugi::xml_node& constants)
{
	// game
	pugi::xml_node game = constants.child("game");
	setPlayers(game.child("PLAYERS").text().as_int());
	setPawns(game.child("PAWNS").text().as_int());
	setPlayerData(game.child("PLAYER_DATA").text().as_int());
	setMovementDelay(game.child("MOVEMENT_DELAY").text().as_int());
}

void Initialization::InitAnimation(pugi::xml_node& constants)
{
	// animation
	pugi::xml_node animation = constants.child("animation");
	setPawnFrames(animation.child("PAWN_FRAMES").text().as_int());
}

void Initialization::InitSpacing(pugi::xml_node& constants)
{
	// spacing
	pugi::xml_node spacing = constants.child("spacing");
	setWinXOff(spacing.child("WIN_X_OFF").text().as_int());
	setWinYOff(spacing.child("WIN_Y_OFF").text().as_int());
	setWinXData(spacing.child("WIN_X_DATA").text().as_int());
	setWinYData(spacing.child("WIN_Y_DATA").text().as_int());
	setWinShadowOff(spacing.child("WIN_SHADOW_OFF").text().as_int());
	setVertOffset(spacing.child("VERT_OFFSET").text().as_int());
}

void Initialization::InitDrawnColors(pugi::xml_node& constants)
{
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
}

void Initialization::InitEnumColors(pugi::xml_node& constants)
{

	//enumColors
}

void Initialization::InitCoordinates(pugi::xml_node& constants)
{
	// coordinates
	pugi::xml_node coordinates = constants.child("coordinates");
	setZeroXPos(coordinates.child("ZERO_X_POS").text().as_int());
	setZeroYPos(coordinates.child("ZERO_Y_POS").text().as_int());
	setZeroXIndex(coordinates.child("ZERO_X_INDEX").text().as_int());
	setZeroYIndex(coordinates.child("ZERO_Y_INDEX").text().as_int());
	setXOff(coordinates.child("X_OFF").text().as_int());
	setYOff(coordinates.child("Y_OFF").text().as_int());
}

void Initialization::InitUI_CONSTANTS(pugi::xml_node& constants)
{

	//UI_CONSTANTS
	pugi::xml_node UI_CONSTANTS = constants.child("UI_CONSTANTS");
	setTitleStart(UI_CONSTANTS.child("TITLE_START").text().as_int());
	setTitleContinue(
			UI_CONSTANTS.child("TITLE_CONTINUE").text().as_int());
	setTitleQuit(UI_CONSTANTS.child("TITLE_QUIT").text().as_int());
	setWinRestart(UI_CONSTANTS.child("WIN_RESTART").text().as_int());
	setWinQuit(UI_CONSTANTS.child("WIN_QUIT").text().as_int());
	setControlsSound(
			UI_CONSTANTS.child("CONTROLS_SOUND").text().as_int());
	setControlsRules(
			UI_CONSTANTS.child("CONTROLS_RULES").text().as_int());
	setControlsQuit(
			UI_CONSTANTS.child("CONTROLS_QUIT").text().as_int());
	setRulesBack(UI_CONSTANTS.child("RULES_BACK").text().as_int());
	setRulesNext(UI_CONSTANTS.child("RULES_NEXT").text().as_int());
	setFadeFactor(UI_CONSTANTS.child("FADE_FACTOR").text().as_int());
	setSliderWidth(
			UI_CONSTANTS.child("SLIDER_WIDTH").text().as_int());
	setSliderHeight(
			UI_CONSTANTS.child("SLIDER_HEIGHT").text().as_int());
	setKnobWidth(UI_CONSTANTS.child("KNOB_WIDTH").text().as_int());
	setKnobHeight(UI_CONSTANTS.child("KNOB_HEIGHT").text().as_int());
}

void Initialization::InitUI_ELEMENTS_PATHS(pugi::xml_node& constants)
{

	// UI_ELEMENTS_PATHS
	pugi::xml_node UI_ELEMENTS_PATHS = constants.child(
			"UI_CONSTANTS");
	setRestartPath(
			UI_ELEMENTS_PATHS.child("RESTART_PATH").text().as_string());
	setContinuePath(
			UI_ELEMENTS_PATHS.child("CONTINUE_PATH").text().as_string());
	setQuitPath(
			UI_ELEMENTS_PATHS.child("QUIT_PATH").text().as_string());
	setSoundOnPath(
			UI_ELEMENTS_PATHS.child("SOUND_ON_PATH").text().as_string());
	setSoundOffPath(
			UI_ELEMENTS_PATHS.child("SOUND_OFF_PATH").text().as_string());
	setRulesPath(
			UI_ELEMENTS_PATHS.child("RULES_PATH").text().as_string());
	setSfxSliderPath(
			UI_ELEMENTS_PATHS.child("SFX_SLIDER_PATH").text().as_string());
	setBgmSliderPath(
			UI_ELEMENTS_PATHS.child("BGM_SLIDER_PATH").text().as_string());
	setSliderKnobPath(
			UI_ELEMENTS_PATHS.child("SLIDER_KNOB_PATH").text().as_string());
}

void Initialization::InitBASIC_PATHS(pugi::xml_node& constants)
{
	//BASIC_PATHS
	pugi::xml_node BASIC_PATHS = constants.child("BASIC_PATHS");
	setFontPath(BASIC_PATHS.child("FONT_PATH").text().as_string());
	setPawnPath(BASIC_PATHS.child("PAWN_PATH").text().as_string());
	setDicePath(BASIC_PATHS.child("DICE_PATH").text().as_string());
	setBoardPath(BASIC_PATHS.child("BOARD_PATH").text().as_string());
	setScrollablePath(
			BASIC_PATHS.child("SCROLLABLE_PATH").text().as_string());
	setWinPath(BASIC_PATHS.child("WIN_PATH").text().as_string());
	setTitlePath(BASIC_PATHS.child("TITLE_PATH").text().as_string());
	setHighlighterPath(
			BASIC_PATHS.child("HIGHLIGHTER_PATH").text().as_string());

}

void Initialization::InitExplosion_FX_DATA(pugi::xml_node& constants)
{
	//Explosion_FX_DATA
	pugi::xml_node Explosion_FX_DATA = constants.child(
			"Explosion_FX_DATA");
	setExplodePath(
			Explosion_FX_DATA.child("EXPLODE_PATH").text().as_string());
	setExplodeWidth(
			Explosion_FX_DATA.child("EXPLODE_WIDTH").text().as_int());
	setExplodeHeight(
			Explosion_FX_DATA.child("EXPLODE_HEIGHT").text().as_int());
	setExplodeFrames(
			Explosion_FX_DATA.child("EXPLODE_FRAMES").text().as_int());
	setExplodeDelay(
			Explosion_FX_DATA.child("EXPLODE_DELAY").text().as_int());
}

void Initialization::InitShockwave_FX_DATA(pugi::xml_node& constants)
{
	//Shockwave_FX_DATA
	pugi::xml_node Shockwave_FX_DATA = constants.child(
			"Shockwave_FX_DATA");
	setShockPath(
			Shockwave_FX_DATA.child("SHOCK_PATH").text().as_string());
	setShockWidth(
			Shockwave_FX_DATA.child("SHOCK_WIDTH").text().as_int());
	setShockHeight(
			Shockwave_FX_DATA.child("SHOCK_HEIGHT").text().as_int());
	setShockFrames(
			Shockwave_FX_DATA.child("SHOCK_FRAMES").text().as_int());
	setShockDelay(
			Shockwave_FX_DATA.child("SHOCK_DELAY").text().as_int());
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

	InitSizes(constants);
	InitGame(constants);
	InitAnimation(constants);
	InitSpacing(constants);
	InitDrawnColors(constants);
	InitCoordinates(constants);
	InitEnumColors(constants);
	InitUI_CONSTANTS(constants);
	InitUI_ELEMENTS_PATHS(constants);
	InitBASIC_PATHS(constants);
	InitExplosion_FX_DATA(constants);
	InitShockwave_FX_DATA(constants);
}

void Initialization::setBoardHeight(int boardHeight)
{
	BOARD_HEIGHT = boardHeight;
}

void Initialization::setBoardLength(int boardLength)
{
	BOARD_LENGTH = boardLength;
}

void Initialization::setBoardWidth(int boardWidth)
{
	BOARD_WIDTH = boardWidth;
}

void Initialization::setButtonHeight(int buttonHeight)
{
	BUTTON_HEIGHT = buttonHeight;
}

void Initialization::setButtonWidth(int buttonWidth)
{
	BUTTON_WIDTH = buttonWidth;
}

void Initialization::setFieldHeight(int fieldHeight)
{
	FIELD_HEIGHT = fieldHeight;
}

void Initialization::setFieldWidth(int fieldWidth)
{
	FIELD_WIDTH = fieldWidth;
}

void Initialization::setFontSize(int fontSize)
{
	FONT_SIZE = fontSize;
}

void Initialization::setHeight(int height)
{
	HEIGHT = height;
}

void Initialization::setRulesHeight(int rulesHeight)
{
	RULES_HEIGHT = rulesHeight;
}

void Initialization::setRulesWidth(int rulesWidth)
{
	RULES_WIDTH = rulesWidth;
}

void Initialization::setSquareSize(int squareSize)
{
	SQUARE_SIZE = squareSize;
}

void Initialization::setWidth(int width)
{
	WIDTH = width;
}

void Initialization::setMovementDelay(int movementDelay)
{
	MOVEMENT_DELAY = movementDelay;
}

void Initialization::setPawns(int pawns)
{
	PAWNS = pawns;
}

void Initialization::setPlayerData(int playerData)
{
	PLAYER_DATA = playerData;
}

void Initialization::setVertOffset(int vertOffset)
{
	VERT_OFFSET = vertOffset;
}
void Initialization::setWinShadowOff(int winShadowOff)
{
	WIN_SHADOW_OFF = winShadowOff;
}

void Initialization::setWinXData(int winXData)
{
	WIN_X_DATA = winXData;
}
void Initialization::setWinXOff(int winXOff)
{
	WIN_X_OFF = winXOff;
}

void Initialization::setWinYData(int winYData)
{
	WIN_Y_DATA = winYData;
}

void Initialization::setBlack(SDL_Color black)
{
	C_BLACK = black;
}

void Initialization::setBlue(SDL_Color blue)
{
	C_BLUE = blue;
}

void Initialization::setGreen(SDL_Color green)
{
	C_GREEN = green;
}

void Initialization::setRed(SDL_Color red)
{
	C_RED = red;
}

void Initialization::setWhite(SDL_Color white)
{
	C_WHITE = white;
}

void Initialization::setXOff(int off)
{
	X_OFF = off;
}

void Initialization::setYOff(int off)
{
	Y_OFF = off;
}

void Initialization::setZeroXIndex(int zeroXIndex)
{
	ZERO_X_INDEX = zeroXIndex;
}

void Initialization::setZeroXPos(int zeroXPos)
{
	ZERO_X_POS = zeroXPos;
}

void Initialization::setZeroYIndex(int zeroYIndex)
{
	ZERO_Y_INDEX = zeroYIndex;
}
void Initialization::setControlsQuit(int controlsQuit)
{
	CONTROLS_QUIT = controlsQuit;
}

void Initialization::setControlsRules(int controlsRules)
{
	CONTROLS_RULES = controlsRules;
}

void Initialization::setControlsSound(int controlsSound)
{
	CONTROLS_SOUND = controlsSound;
}

void Initialization::setFadeFactor(int fadeFactor)
{
	FADE_FACTOR = fadeFactor;
}

void Initialization::setKnobHeight(int knobHeight)
{
	KNOB_HEIGHT = knobHeight;
}

void Initialization::setKnobWidth(int knobWidth)
{
	KNOB_WIDTH = knobWidth;
}

void Initialization::setRulesBack(int rulesBack)
{
	RULES_BACK = rulesBack;
}

void Initialization::setRulesNext(int rulesNext)
{
	RULES_NEXT = rulesNext;
}

void Initialization::setSliderHeight(int sliderHeight)
{
	SLIDER_HEIGHT = sliderHeight;
}

void Initialization::setSliderWidth(int sliderWidth)
{
	SLIDER_WIDTH = sliderWidth;
}
void Initialization::setTitleContinue(int titleContinue)
{
	TITLE_CONTINUE = titleContinue;
}

void Initialization::setTitleQuit(int titleQuit)
{
	TITLE_QUIT = titleQuit;
}

void Initialization::setTitleStart(int titleStart)
{
	TITLE_START = titleStart;
}

void Initialization::setWinQuit(int winQuit)
{
	WIN_QUIT = winQuit;
}

void Initialization::setBgmSliderPath(const string& bgmSliderPath)
{
	BGM_SLIDER_PATH = bgmSliderPath;
}

void Initialization::setContinuePath(const string& continuePath)
{
	CONTINUE_PATH = continuePath;
}

void Initialization::setQuitPath(const string& quitPath)
{
	QUIT_PATH = quitPath;
}

void Initialization::setRestartPath(const string& restartPath)
{
	RESTART_PATH = restartPath;
}

void Initialization::setRulesPath(const string& rulesPath)
{
	RULES_PATH = rulesPath;
}

void Initialization::setSfxSliderPath(const string& sfxSliderPath)
{
	SFX_SLIDER_PATH = sfxSliderPath;
}

void Initialization::setSliderKnobPath(const string& sliderKnobPath)
{
	SLIDER_KNOB_PATH = sliderKnobPath;
}

void Initialization::setSoundOffPath(const string& soundOffPath)
{
	SOUND_OFF_PATH = soundOffPath;
}

void Initialization::setSoundOnPath(const string& soundOnPath)
{
	SOUND_ON_PATH = soundOnPath;
}

void Initialization::setBoardPath(const string& boardPath)
{
	BOARD_PATH = boardPath;
}

void Initialization::setDicePath(const string& dicePath)
{
	DICE_PATH = dicePath;
}

void Initialization::setFontPath(const string& fontPath)
{
	FONT_PATH = fontPath;
}

void Initialization::setHighlighterPath(const string& highlighterPath)
{
	HIGHLIGHTER_PATH = highlighterPath;
}

void Initialization::setPawnPath(const string& pawnPath)
{
	PAWN_PATH = pawnPath;
}

void Initialization::setScrollablePath(const string& scrollablePath)
{
	SCROLLABLE_PATH = scrollablePath;
}

void Initialization::setTitlePath(const string& titlePath)
{
	TITLE_PATH = titlePath;
}

void Initialization::setExplodeDelay(int explodeDelay)
{
	EXPLODE_DELAY = explodeDelay;
}

void Initialization::setExplodeFrames(int explodeFrames)
{
	EXPLODE_FRAMES = explodeFrames;
}

void Initialization::setExplodeHeight(int explodeHeight)
{
	EXPLODE_HEIGHT = explodeHeight;
}

void Initialization::setExplodePath(const string& explodePath)
{
	EXPLODE_PATH = explodePath;
}

void Initialization::setShockDelay(int shockDelay)
{
	SHOCK_DELAY = shockDelay;
}

void Initialization::setShockFrames(int shockFrames)
{
	SHOCK_FRAMES = shockFrames;
}

void Initialization::setShockHeight(int shockHeight)
{
	SHOCK_HEIGHT = shockHeight;
}

void Initialization::setShockPath(const string& shockPath)
{
	SHOCK_PATH = shockPath;
}

void Initialization::setShockWidth(int shockWidth)
{
	SHOCK_WIDTH = shockWidth;
}

void Initialization::setExplodeWidth(int explodeWidth)
{
	EXPLODE_WIDTH = explodeWidth;
}

void Initialization::setWinPath(const string& winPath)
{
	WIN_PATH = winPath;
}

void Initialization::setStartPath(const string& startPath)
{
	START_PATH = startPath;
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
