///Shared constants file

#ifndef SHARED_H
#define SHARED_H

#include <string>
using std::string;
using std::pair;

///Quit flag
extern bool quit;

///Screen constants
#define WIDTH 800
#define HEIGHT 800

//Scrollable field constants
#define FIELD_WIDTH 2412
#define FIELD_HEIGHT 1608

///Playing squares count
#define BOARD_LENGTH 46

///Board dimensions
#define BOARD_WIDTH 15
#define BOARD_HEIGHT 15

///Square dimensions
#define SQUARE_SIZE 48

///Number of players
#define PLAYERS 3

///Number of pawns
#define PAWNS 5

///Pawn sprite animation frames
#define PAWN_FRAMES 20

///UI button size
#define BUTTON_WIDTH 200
#define BUTTON_HEIGHT 54

///Win screen data spacing
#define WIN_X_OFF 135
#define WIN_Y_OFF 325
#define WIN_X_DATA 130
#define WIN_Y_DATA 50
#define WIN_SHADOW_OFF 4

///Rule screen button params
#define RULES_WIDTH 100
#define RULES_HEIGHT 100

///Player data amount
#define PLAYER_DATA 5

///Drawing colors
#define C_WHITE {255,255,255,255}
#define C_BLACK {0,0,0,255}
#define C_RED {255,0,0,255}
#define C_BLUE {0,255,0,255}
#define C_GREEN {0,0,255,255}
#define C_YELLOW {255,255,0,255}

///Player colors
enum Colors{
	NONE=0, YELLOW, RED, BLUE
};

///Pawn start positions (in game squares)
const unsigned START_POS[]{
	0, ///YELLOW
	14,///RED
	28 ///BLUE
};


///Pawn waiting positions (in screen pixels)
const pair<int,int> IDLE_POS[5]{
	{279, 40}, ///YELLOW
	{39, 474}, ///RED
	{475, 713} ///BLUE
};

///Top row leftmost square coordinates
#define ZERO_X_POS 329
#define ZERO_Y_POS 40

///Top row leftmost square index
#define ZERO_X_INDEX 6
#define ZERO_Y_INDEX 0

///Graphics draw offset
#define X_OFF 60
#define Y_OFF 40

///Active board
const bool MOVEABLE_SQUARES[BOARD_HEIGHT][BOARD_HEIGHT]{
	{0,0,0,0,0,0,1,1,1,0,0,0,0,0,0},
	{0,0,0,0,0,0,1,1,1,0,0,0,0,0,0},
	{0,0,0,0,0,0,1,1,1,0,0,0,0,0,0},
	{0,0,0,0,0,0,1,1,1,0,0,0,0,0,0},
	{0,0,0,0,0,0,1,1,1,0,0,0,0,0,0},
	{0,0,0,0,0,1,1,1,1,1,0,0,0,0,0},
	{1,1,1,1,1,1,0,0,0,1,0,0,0,0,0},
	{1,1,1,1,1,1,0,0,0,1,0,0,0,0,0},
	{1,1,1,1,1,1,0,0,0,1,0,0,0,0,0},
	{0,0,0,0,0,1,1,1,1,1,0,0,0,0,0},
	{0,0,0,0,0,0,1,1,1,0,0,0,0,0,0},
	{0,0,0,0,0,0,1,1,1,0,0,0,0,0,0},
	{0,0,0,0,0,0,1,1,1,0,0,0,0,0,0},
	{0,0,0,0,0,0,1,1,1,0,0,0,0,0,0},
	{0,0,0,0,0,0,1,1,1,0,0,0,0,0,0}
};

///Next square location in (x,y)
const pair<int,int> NEXT_SQUARE[BOARD_HEIGHT][BOARD_WIDTH]{
	{	{ 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0 ,0}, { 0, 0}, { 0, 1}, {-1, 0}, {-1, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}	},
	{	{ 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 1}, { 0, 1}, { 0,-1}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}	},
	{	{ 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 1}, { 0, 1}, { 0,-1}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}	},
	{	{ 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 1}, { 0, 1}, { 0,-1}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}	},
	{	{ 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 1}, { 0, 1}, { 0,-1}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}	},
	{	{ 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 1}, {-1, 0}, { 0, 1}, { 0,-1}, {-1, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}	},
	{	{ 0, 1}, {-1, 0}, {-1, 0}, {-1, 0}, {-1, 0}, {-1, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0,-1}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}	},
	{	{ 0, 1}, { 1, 0}, { 1, 0}, { 1, 0}, { 1, 0}, { 1, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0,-1}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}	},
	{	{ 1, 0}, { 1, 0}, { 1, 0}, { 1, 0}, { 1, 0}, { 0, 1}, { 0, 0}, { 0, 0}, { 0, 0}, { 0,-1}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}	},
	{	{ 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 1, 0}, { 0, 1}, { 0,-1}, { 1, 0}, { 0,-1}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}	},
	{	{ 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 1}, { 0,-1}, { 0,-1}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}	},
	{	{ 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 1}, { 0,-1}, { 0,-1}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}	},
	{	{ 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 1}, { 0,-1}, { 0,-1}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}	},
	{	{ 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 1}, { 0,-1}, { 0,-1}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}	},
	{	{ 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}, { 1, 0}, { 1, 0}, { 0,-1}, { 0, 0}, { 0, 0}, { 0 ,0}, { 0, 0}, { 0, 0}, { 0, 0}	}
};

///Player-specific safe squares direction (x,y)
const pair<int,int> NEXT_SAFE[]{
	{0,1}, ///YELLOW
	{1,0}, ///RED
	{0,-1} ///BLUE
};

///Active squares on board
const pair<int,int> ACTIVE_SQUARES[BOARD_LENGTH]{
											  {6,0},  {7,0},  {8,0},
											  {6,1},		  {8,1},
											  {6,2},		  {8,2},
											  {6,3},		  {8,3},
											  {6,4},		  {8,4},
									   {5,5}, {6,5},		  {8,5}, {9,5},
	{0,6}, {1,6}, {2,6}, {3,6}, {4,6}, {5,6},						 {9,6},
	{0,7},														     {9,7},
	{0,8}, {1,8}, {2,7}, {3,8}, {4,8}, {5,8},					     {8,8},
									   {5,9}, {6,9},		  {8,9}, {9,9},
											  {6,10},		  {8,10},
											  {6,11},		  {8,11},
											  {6,12},		  {8,12},
											  {6,13},		  {8,13},
											  {6,14}, {7,14}, {8,14}
};

///Safe squares on board
const pair<int,int> SAFE_SQUARES[PLAYERS][PAWNS]{
	{ {7,1}, {7,2}, {7,3}, {7,4}, {7,5} },	   ///YELLOW
	{ {1,7}, {2,7}, {3,7}, {4,7}, {5,7} },     ///RED
	{ {7,9}, {7,10}, {7,11}, {7,12}, {7,13} }  ///BLUE
};

///Final squares on board
const pair<int,int> FINAL_SQUARES[PLAYERS]{
	{7,6}, ///YELLOW
	{6,7}, ///RED
	{7,8}  ///BLUE
};

///Base squares on board
const pair<int,int> BASE_SQUARES[PLAYERS][PAWNS]{
	{ {1,0}, {2,0}, {3,0}, {1,1}, {3,1} },			///YELLOW
	{ {0,11}, {0,12}, {0,13}, {1,11}, {1,13} },		///RED
	{ {11,13}, {13,13}, {11,14}, {12,14}, {13,14} }	///BLUE
};

///Start squares on board
const pair<int,int> START_SQUARES[PLAYERS]{
	{6,0}, ///YELLOW
	{0,8}, ///RED
	{8,14} ///BLUE
};

///Safe zone entry points
const pair<int,int> ENTRY_SQUARES[PLAYERS]{
	{7,0}, ///YELLOW
	{0,7}, ///RED
	{7,14} ///BLUE
};

///Sprite sizes (pixels)
const float SPRITE_SCALE[]{
	1,	 ///1 sprite per square
	0.5, ///2 sprites per square
	0.5, ///3 sprites per square
	0.5, ///4 sprites per square
	0.5	 ///5 sprites per square
};

///Pawn positions on square
const pair<int,int> PAWN_LAYOUT[]{
	{1,1},{0,0},{2,0},
	{0,2},{2,2}
};

///UI screen coordinates
const pair<int,int> SCREEN_COORDS[]{
	{    0,   0}, //BLANK
	{ -800,   0}, //RULES1
	{-1600,   0}, //RULES2
	{    0, -800}, //TITLE
	{ -800, -800}, //GAME
	{-1600, -800}  //WIN
};

///Font size
#define FONT_SIZE 20

///Font path
#define FONT_PATH "./GFX/font.ttf"

///Pawn sprite path
#define PAWN_PATH "./GFX/bomb.png"

///Dice texture path
#define DICE_PATH "./GFX/dice.png"

///Board texture path
#define BOARD_PATH "./GFX/board.png"

///Scrollable field path
#define SCROLLABLE_PATH "./GFX/scrollable.png"

///Win screen background path
#define WIN_PATH "./GFX/win.png"

///Title screen background path
#define TITLE_PATH "./GFX/title.png"

///UI button vertical offset
#define VERT_OFFSET 100

///Player dice positions (in pixels)
const pair<int,int> DICE_POS[]{
	{115,153}, ///YELLOW
	{186,565}, ///RED
	{598,491} ////BLUE
};

///UI constants
#define TITLE_START 0b100
#define TITLE_CONTINUE 0b010
#define TITLE_QUIT 0b001
#define WIN_RESTART 0b01
#define WIN_QUIT 0b10
#define CONTROLS_SOUND 0b100
#define CONTROLS_RULES 0b010
#define CONTROLS_QUIT 0b001
#define RULES_BACK 0b01
#define RULES_NEXT 0b10

///Rulebook images path
#define RULES_1_PATH "./GFX/Rules of LUDO/1.png"
#define RULES_2_PATH "./GFX/Rules of LUDO/2.png"
#define RULES_3_PATH "./GFX/Rules of LUDO/3.png"
#define RULES_4_PATH "./GFX/Rules of LUDO/4.png"

///UI elements location
#define START_PATH "./GFX/button_start.png"
#define RESTART_PATH "./GFX/button_restart.png"
#define CONTINUE_PATH "./GFX/button_continue.png"
#define QUIT_PATH "./GFX/button_quit.png"
#define SOUND_ON_PATH "./GFX/button_sound_on.png"
#define SOUND_OFF_PATH "./GFX/button_sound_off.png"
#define RULES_PATH "./GFX/button_rules.png"

///Square highlighter path
#define HIGHLIGHTER_PATH "./GFX/highlight.png"

///BGM
#define BGM menuS

///SFX
#define BUTTON_SFX click
#define ON_MOVE typing
#define ON_COLLISION explosion
#define ON_ACTIVATION jump
#define ON_ROLL DiceRoll
#define ON_SIX orchHit
#define ON_DICE ding

///UI fade speed
#define FADE_FACTOR 10

///Explosion FX data
#define EXPLODE_PATH "./GFX/explode.png"
#define EXPLODE_WIDTH 50
#define EXPLODE_HEIGHT 105
#define EXPLODE_FRAMES 9
#define EXPLODE_DELAY 100

///Shockwave FX data
#define SHOCK_PATH "./GFX/shockwave.png"
#define SHOCK_WIDTH 327
#define SHOCK_HEIGHT 304
#define SHOCK_FRAMES 5
#define SHOCK_DELAY 50

///Pawn movement delay
#define MOVEMENT_DELAY 400

///Debug mode
#define DEBUG

#endif
