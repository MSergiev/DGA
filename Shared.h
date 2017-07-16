//Shared constants file

#ifndef SHARED_H
#define SHARED_H

#include <string>
using std::string;
using std::pair;

//Screen constants
#define WIDTH 800
#define HEIGHT 800

//Playing squares count
#define BOARD_LENGTH 46

//Square dimensions
#define SQUARE_SIZE 48

//Player colors
enum Colors{
	NONE=0, YELLOW, RED, BLUE
};

//Pawn start positions (in game squares)
const unsigned START_POS[]{
	0, //YELLOW
	14,//RED
	28 //BLUE
};


//Pawn waiting positions (in screen pixels)
const unsigned IDLE_POS[5][2]{
	{279, 40}, //YELLOW
	{39, 474}, //RED
	{475, 713} //BLUE
};

//Top row leftmost square coordinates
#define ZERO_X_POS 329
#define ZERO_Y_POS 40

//Next square location in (x,y)
const pair<int, int> NEXT_SQUARE[]{
	{0,1},{0,1},{0,1},{0,1},{0,1},
	{-1,0},{0,1},
	{-1,0},{-1,0},{-1,0},{-1,0},{-1,0},
	{0,1},{0,1},
	{1,0},{1,0},{1,0},{1,0},{1,0},
	{0,1},{1,0},
	{0,1},{0,1},{0,1},{0,1},{0,1},
	{1,0},{1,0},
	{0,-1},{0,-1},{0,-1},{0,-1},{0,-1},
	{1,0},{0,-1},{0,-1},{0,-1},{0,-1},
	{-1,0},{0,-1},{0,-1},{0,-1},{0,-1},{0,-1},
	{-1,0}
};

//Player-specific squares direction (x,y)
const pair<int,int> FINAL_SQUARE[]{
	{0,1}, //YELLOW
	{1,0}, //RED
	{0,-1} //BLUE
};

//Font path
#define FONT_PATH "./GFX/font.ttf"

//Pawn sprite path
#define PAWN_PATH "./GFX/bomb.png"

//Dice texture path
#define DICE_PATH "./GFX/dice.png"

//Board texture path
#define BOARD_PATH "./GFX/board.png"

//Debug mode
#define DEBUG

#endif
