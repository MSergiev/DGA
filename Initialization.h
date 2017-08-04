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

#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::pair;
using std::string;

class Initialization
{
public:
	Initialization();
	virtual ~Initialization();

	static int WIDTH;
	static int HEIGHT;
	static int FIELD_WIDTH;
	static int FIELD_HEIGHT;
	static int BOARD_LENGTH;
	static int BOARD_WIDTH;
	static int BOARD_HEIGHT;
	static int SQUARE_SIZE;
	static int BUTTON_WIDTH;
	static int BUTTON_HEIGHT;
	static int FONT_SIZE;
	static int RULES_WIDTH;
	static int RULES_HEIGHT;

	static int PLAYERS;
	static int PAWNS;
	static int PLAYER_DATA;
	static int MOVEMENT_DELAY;

	static int PAWN_FRAMES;
	static const float SPRITE_SCALE[];

	static int WIN_X_OFF;
	static int WIN_Y_OFF;
	static int WIN_X_DATA;
	static int WIN_Y_DATA;
	static int WIN_SHADOW_OFF;
	static int VERT_OFFSET;

	static SDL_Color C_WHITE;
	static SDL_Color C_BLACK;
	static SDL_Color C_RED;
	static SDL_Color C_BLUE;
	static SDL_Color C_GREEN;
	static SDL_Color C_YELLOW;

	static enum Colors
	{
	};

	static int ZERO_X_POS;
	static int ZERO_Y_POS;
	static int ZERO_X_INDEX;
	static int ZERO_Y_INDEX;
	static int X_OFF;
	static int Y_OFF;

	static const unsigned START_POS[];
	static const pair<int, int> IDLE_POS[5];
	static const bool MOVEABLE_SQUARES[BOARD_HEIGHT][BOARD_WIDTH];
	static const pair<int, int> NEXT_SQUARE[BOARD_HEIGHT][BOARD_WIDTH];
	static const pair<int, int> NEXT_SAFE[];
	static const pair<int, int> ACTIVE_SQUARES[BOARD_LENGTH];
	static const pair<int, int> SAFE_SQUARES[PLAYERS][PAWNS];
	static const pair<int, int> FINAL_SQUARES[PLAYERS];
	static const pair<int, int> BASE_SQUARES[PLAYERS][PAWNS];
	static const pair<int, int> START_SQUARES[PLAYERS];
	static const pair<int, int> ENTRY_SQUARES[PLAYERS];
	static const pair<int, int> PAWN_LAYOUT[];
	static const pair<int, int> SCREEN_COORDS[];
	static const pair<int, int> DICE_POS[];

	static int TITLE_START;
	static int TITLE_CONTINUE;
	static int TITLE_QUIT;
	static int WIN_RESTART;
	static int WIN_QUIT;
	static int CONTROLS_SOUND;
	static int CONTROLS_RULES;
	static int CONTROLS_QUIT;
	static int RULES_BACK;
	static int RULES_NEXT;
	static int FADE_FACTOR;
	static int SLIDER_WIDTH;
	static int SLIDER_HEIGHT;
	static int KNOB_WIDTH;
	static int KNOB_HEIGHT;

	static string FONT_PATH;
	static string PAWN_PATH;
	static string DICE_PATH;
	static string BOARD_PATH;
	static string SCROLLABLE_PATH;
	static string WIN_PATH;
	static string TITLE_PATH;
	static string HIGHLIGHTER_PATH;

	static string START_PATH;
	static string RESTART_PATH;
	static string CONTINUE_PATH;
	static string QUIT_PATH;
	static string SOUND_ON_PATH;
	static string SOUND_OFF_PATH;
	static string RULES_PATH;
	static string SFX_SLIDER_PATH;
	static string BGM_SLIDER_PATH;
	static string SLIDER_KNOB_PATH;

	static string EXPLODE_PATH;
	static int EXPLODE_WIDTH;
	static int EXPLODE_HEIGHT;
	static int EXPLODE_FRAMES;
	static int EXPLODE_DELAY;

	static string SHOCK_PATH;
	static int SHOCK_WIDTH;
	static int SHOCK_HEIGHT;
	static int SHOCK_FRAMES;
	static int SHOCK_DELAY;
};

#endif /* INITIALIZATION_H_ */
