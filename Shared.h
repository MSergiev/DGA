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
#define LENGTH 56

//Square dimensions
#define SQUARE_SIZE 48

//Player colors
enum Colors{
	RED=0, BLUE, YELLOW
};

//Player start positions
const unsigned START_POS[3][2]{
	{329, 40}, //YELLOW
	{39, 472}, //RED
	{425, 713} //BLUE
};

//Board square layout
const bool LAYOUT[15][10]{
	{0,0,0,0,0,0,1,1,1,0},
	{0,0,0,0,0,0,1,1,1,0},
	{0,0,0,0,0,0,1,1,1,0},
	{0,0,0,0,0,0,1,1,1,0},
	{0,0,0,0,0,0,1,1,1,0},
	{1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1},
	{0,0,0,0,0,1,1,1,1,1},
	{0,0,0,0,0,0,1,1,1,0},
	{0,0,0,0,0,0,1,1,1,0},
	{0,0,0,0,0,0,1,1,1,0},
	{0,0,0,0,0,0,1,1,1,0},
	{0,0,0,0,0,0,1,1,1,0}
};

#endif
