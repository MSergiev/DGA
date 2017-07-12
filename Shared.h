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
	NONE, RED, BLUE, YELLOW
};

//Player start positions (in game squares)
const unsigned START_POS[]{
	0, //YELLOW
	14, //RED
	28 //BLUE
};


#endif
